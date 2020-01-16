/*-
 * Copyright (c) 2020 Ruslan Bukin <br@bsdpad.com>
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
#include <sys/time.h>

#include "nrf_rtc.h"

#define	RD4(_sc, _reg)		\
	*(volatile uint32_t *)((_sc)->base + _reg)
#define	WR4(_sc, _reg, _val)	\
	*(volatile uint32_t *)((_sc)->base + _reg) = _val

void
nrf_rtc_intr(void *arg, struct trapframe *tf, int irq)
{
	struct nrf_rtc_softc *sc;

	sc = arg;

	WR4(sc, RTC_EVENTS_OVRFLW, 0);

	sc->ts.tv_sec += sc->period;
}

void
nrf_rtc_init(struct nrf_rtc_softc *sc,
    uint32_t base, uint16_t prescaler)
{

	sc->base = base;
	sc->prescaler = prescaler;
	sc->freq = (32768 / (sc->prescaler + 1));
	sc->period = 0x1000000 / sc->freq;
}

static int
nrf_rtc_settime(const struct timespec *tp, void *arg)
{
	struct nrf_rtc_softc *sc;

	sc = arg;

	sc->ts.tv_sec = tp->tv_sec;
	sc->ts.tv_nsec = tp->tv_nsec;

	WR4(sc, RTC_TASKS_STOP, 1);
	WR4(sc, RTC_TASKS_CLEAR, 1);
	WR4(sc, RTC_PRESCALER, sc->prescaler);
	WR4(sc, RTC_INTENSET, INTENSET_OVRFLW);
	WR4(sc, RTC_TASKS_START, 1);

	return (0);
}

static int
nrf_rtc_gettime(struct timespec *tp, void *arg)
{
	struct nrf_rtc_softc *sc;
	int cnt;
	time_t sec;
	long nsec;

	sc = arg;

again:
	critical_enter();

	/* A counter overflow could happen here, but interrupts are disabled */

	cnt = RD4(sc, RTC_COUNTER);

	if (RD4(sc, RTC_EVENTS_OVRFLW)) {
		critical_exit();

		/* An overflow interrupt must arise here. */

		goto again;
	}

	sec = cnt / sc->freq;
	nsec = (1000000000 / sc->freq) * (cnt % sc->freq);

	tp->tv_nsec = sc->ts.tv_nsec + nsec;
	tp->tv_sec = sc->ts.tv_sec + sec;

	critical_exit();

	if (tp->tv_nsec >= 1000000000) {
		tp->tv_nsec -= 1000000000;
		tp->tv_sec += 1;
	}

	return (0);
}

struct rtc_driver nrf_rtc_driver = {
	.settime = nrf_rtc_settime,
	.gettime = nrf_rtc_gettime,
};