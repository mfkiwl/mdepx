/*-
 * Copyright (c) 2019 Ruslan Bukin <br@bsdpad.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
#include <sys/systm.h>
#include <sys/thread.h>
#include <sys/mutex.h>
#include <sys/spinlock.h>
#include <sys/pcpu.h>

#include <machine/atomic.h>

#define	MUTEX_DEBUG
#undef	MUTEX_DEBUG

#ifdef	MUTEX_DEBUG
#define	dprintf(fmt, ...)	printf(fmt, ##__VA_ARGS__)
#else
#define	dprintf(fmt, ...)
#endif

struct token {
	struct thread *td;
	struct mtx *m;
	bool timeout;
};

static void
mtx_cb(void *arg)
{
	struct thread *td;
	struct token *t;
	struct mtx *m;

	t = arg;
	m = t->m;
	td = t->td;

	KASSERT(curthread->td_critnest > 0,
	    ("Not in critical section"));

	sl_lock(&m->l);

	if (td->td_state == TD_STATE_UNLOCK) {
		/* too late */
		sl_unlock(&m->l);
		return;
	}
	t->timeout = 1;

	KASSERT(td->td_state == TD_STATE_ACK,
	    ("%s: wrong state %d\n", __func__, td->td_state));

	if (td->td_next != NULL)
		td->td_next->td_prev = td->td_prev;
	else
		m->td_last = td->td_prev;

	if (td->td_prev != NULL)
		td->td_prev->td_next = td->td_next;
	else
		m->td_first = td->td_next;

	sched_lock();
	td->td_state = TD_STATE_WAKEUP;
	sched_add(td);
	sched_unlock();
	sl_unlock(&m->l);
}

int
mtx_timedlock(struct mtx *m, int ticks)
{
	struct token t;
	struct thread *td;
	uintptr_t tid;
	int ret;

	td = curthread;

	KASSERT(td->td_idle == 0,
	    ("Can't lock mutex from idle thread"));

	tid = (uintptr_t)td;

	for (;;) {
		critical_enter();
		sl_lock(&m->l);
		ret = atomic_cmpset_acq_ptr(&(m)->mtx_lock, 0, (tid));
		if (ret) {
			/* Lock acquired. */
			sl_unlock(&m->l);
			critical_exit();
			break;
		}

		/* Lock is owned by another thread, sleep. */
		callout_cancel(&td->td_c);
		callout_init(&td->td_c);
		t.td = td;
		t.m = m;
		t.timeout = 0;
		if (ticks)
			callout_set(&td->td_c, ticks, mtx_cb, &t);

		td->td_state = TD_STATE_MUTEX_WAIT;

		if (m->td_first == NULL) {
			td->td_next = NULL;
			td->td_prev = NULL;
			m->td_first = td;
			m->td_last = td;
		} else {
			td->td_prev = m->td_last;
			td->td_next = NULL;
			m->td_last->td_next = td;
			m->td_last = td;
		}
		sl_unlock(&m->l);
		critical_exit();

		md_thread_yield();

		/*
		 * We are here by one of the reasons:
		 * 1. mtx_unlock adds us to the sched
		 * 2. mtx_cb added us to the sched
		 *
		 * td_c is cancelled here
		 */

		if (ticks && t.timeout)
			return (0);
	}

	return (1);
}

void
mtx_lock(struct mtx *m)
{

	mtx_timedlock(m, 0);
}

int
mtx_trylock(struct mtx *m)
{
	uintptr_t tid;
	int ret;

	tid = (uintptr_t)curthread;

	ret = atomic_cmpset_acq_ptr(&(m)->mtx_lock, 0, (tid));
	if (ret) {
		/* Lock acquired. */
		return (1);
	}

	return (0);
}

int
mtx_unlock(struct mtx *m)
{
	struct thread *td;
	uintptr_t tid;

	tid = (uintptr_t)curthread;

	critical_enter();
	sl_lock(&m->l);

	if (!atomic_cmpset_rel_ptr(&(m)->mtx_lock, (tid), 0))
		panic("Can't unlock mutex.\n");

	td = m->td_first;
	if (td) {
		/* Someone is waiting for the mutex. */
		m->td_first = td->td_next;
		if (td->td_next != NULL)
			td->td_next->td_prev = NULL;
		else
			m->td_last = NULL;

		/* Ensure td left CPU. */
		while (td->td_state != TD_STATE_ACK);

		/*
		 * Ensure mtx_cb will not pick up this thread just
		 * after sl_unlock() and before callout_cancel().
		 */
		td->td_state = TD_STATE_UNLOCK;
		sl_unlock(&m->l);

		/* mtx_cb could be called here by another CPU. */

		callout_cancel(&td->td_c);

		sched_lock();
		KASSERT(td->td_state == TD_STATE_UNLOCK, ("wrong state"));
		td->td_state = TD_STATE_WAKEUP;
		KASSERT(td != curthread, ("td is curthread"));
		sched_add(td);
		sched_unlock();
	} else
		sl_unlock(&m->l);

	critical_exit();

	return (1);
}
