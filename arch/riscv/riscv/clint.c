/*-
 * Copyright (c) 2017-2021 Ruslan Bukin <br@bsdpad.com>
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

/* Core Local Interruptor (CLINT) */

#include <sys/cdefs.h>
#include <sys/pcpu.h>
#include <sys/smp.h>
#include <sys/systm.h>
#include <sys/io.h>
#include <sys/of.h>
#include <sys/cheri.h>

#include <machine/atomic.h>
#include <machine/cpuregs.h>
#include <machine/sbi.h>

#include <machine/clint.h>

#define	RD4(_sc, _reg)		\
	mdx_ioread_uint32((_sc)->base, _reg)
#define	RD8(_sc, _reg)		\
	mdx_ioread_uint64((_sc)->base, _reg)

#define	WR4(_sc, _reg, _val)	\
	mdx_iowrite_uint32((_sc)->base, _reg, _val)
#define	WR8(_sc, _reg, _val)	\
	mdx_iowrite_uint64((_sc)->base, _reg, _val)

#define	CLINT_DEBUG
#undef	CLINT_DEBUG

#ifdef	CLINT_DEBUG
#define	dprintf(fmt, ...)	printf(fmt, ##__VA_ARGS__)
#else
#define	dprintf(fmt, ...)
#endif

static struct clint_softc *clint_sc;

#if defined(MDX_OF) && !defined(MDX_RISCV_SUPERVISOR_MODE)
static struct mdx_compat_data clint_compat_data[] = {
	{ "riscv,clint0" },
	{ NULL },
};
#endif

#ifdef MDX_SCHED_SMP
extern struct entry pcpu_all;

void
send_ipi(int cpumask, int ipi)
{
	struct pcpu *p;

	KASSERT(MDX_CPU_MAX <= 32, ("cpumask is 32 bit"));
	KASSERT(!list_empty(&pcpu_all), ("no cpus"));

	for (p = CONTAINER_OF(pcpu_all.next, struct pcpu, pc_all);;
	    (p = CONTAINER_OF(p->pc_all.next, struct pcpu, pc_all))) {
		if (cpumask & (1 << p->pc_cpuid)) {
			atomic_set_32(&p->pc_pending_ipis, ipi);
			clint_set_sip(p->pc_cpuid);
		}
		if (p->pc_all.next == &pcpu_all)
			break;
	}
}

void
clint_intr_software(void)
{
	struct clint_softc *sc;
	int cpuid;

	sc = clint_sc;

	cpuid = PCPU_GET(cpuid);

	WR4(sc, MSIP(cpuid), 0);

	ipi_handler();
}
#endif

void
clint_set_sip(int hart_id)
{
	struct clint_softc *sc;

	sc = clint_sc;

	WR4(sc, MSIP(hart_id), 1);
}

void
clint_intr(void)
{
	struct clint_softc *sc;

	dprintf("%s\n", __func__);

	sc = clint_sc;

	csr_clear_tie();

	mdx_callout_callback(&sc->mt);
}

static void
clint_stop(void *arg)
{

	csr_clear_tie();
	csr_clear_tip();
}

#if __riscv_xlen == 64
static void
clint_set_timer(struct clint_softc *sc, int cpuid, uint64_t new)
{

#ifndef MDX_RISCV_SUPERVISOR_MODE
	WR8(sc, MTIMECMP(cpuid), new);
#else
	sbi_set_timer(new);
#endif
}
#endif

static void
clint_start(void *arg, uint32_t ticks)
{
	struct clint_softc *sc;
	int cpuid;

	sc = arg;

	cpuid = PCPU_GET(cpuid);

	dprintf("%s: ticks %u\n", __func__, ticks);
	dprintf("%s%d: ticks %u\n", __func__, cpuid, ticks);

#if __riscv_xlen == 64
	uint64_t val;
	uint64_t new;

	val = csr_read64(time);
	new = val + ticks;
	clint_set_timer(sc, cpuid, new);
#else
	/*
	 * Machine-mode only.
	 * TODO: support for 32-bit supervisor-mode.
	 */
	uint32_t low, high;
	uint32_t new;

	low = RD4(sc, MTIME);
	high = RD4(sc, MTIME + 0x4);
	new = low + ticks;
	dprintf("%s%d: ticks %u, low %u, high %u, new %u\n",
	    __func__, PCPU_GET(cpuid), ticks, low, high, new);
	if (new < low)
		high += 1;
	WR4(sc, MTIMECMP(cpuid) + 0x4, high);
	WR4(sc, MTIMECMP(cpuid), new);
#endif

	csr_set_tie();
}

static ticks_t
clint_mtime(void *arg)
{
	ticks_t low;

#ifdef MDX_RISCV_SUPERVISOR_MODE
#if __riscv_xlen == 64
	low = csr_read(time);
#else
	low = csr_read64(time);
#endif
#else
	struct clint_softc *sc;

	sc = arg;

#if __riscv_xlen == 64
	low = RD4(sc, MTIME);
#else
	low = RD8(sc, MTIME);
#endif
#endif

	return (low);
}

void
clint_udelay(struct clint_softc *sc,
    uint32_t usec, uint32_t osc_freq)
{
	ticks_t first, last;
	ticks_t delta;
	ticks_t counts;

	counts = 0;
	first = clint_mtime(sc);
	while (counts < usec) {
		last = clint_mtime(sc);
		if (last > first)
			delta = last - first;
		else
			delta = last + (0xffffffff - first) + 1;

		counts += (delta * (1000000 / osc_freq));

		first = last;
	}
}

static int
clint_measure_cpu_freq(struct clint_softc *sc, uint32_t osc_freq, int n)
{
	u_long start_mcycle, delta_mcycle;
	u_long start_mtime, delta_mtime;
	u_long mtime_freq;
	u_long tmp;
	int freq;

	tmp = clint_mtime(sc);
	do {
		start_mtime = clint_mtime(sc);
	} while (start_mtime == tmp);

	start_mcycle = csr_read(mcycle);

	do {
		delta_mtime = (clint_mtime(sc) - start_mtime);
	} while (delta_mtime < n);

	delta_mcycle = (csr_read(mcycle) - start_mcycle);

	mtime_freq = osc_freq;

	freq = (delta_mcycle / delta_mtime) * mtime_freq;
	freq += ((delta_mcycle % delta_mtime) * mtime_freq) / delta_mtime;

	return (freq);
}

int
clint_get_cpu_freq(struct clint_softc *sc, uint32_t osc_freq)
{
	int cpu_freq;

	/* warm up I$ */
	clint_measure_cpu_freq(sc, osc_freq, 1);

	cpu_freq = clint_measure_cpu_freq(sc, osc_freq, 10);

	return (cpu_freq);
}

int
clint_init(struct clint_softc *sc, capability base,
    uint32_t frequency)
{

	if (clint_sc != NULL)
		return (MDX_EEXIST);

	clint_sc = sc;
	sc->base = base;

	sc->mt.start = clint_start;
	sc->mt.stop = clint_stop;
	sc->mt.count = clint_mtime;
	sc->mt.maxcnt = 0xffffffff;
	sc->mt.frequency = frequency;
	sc->mt.arg = sc;

	mdx_callout_register(&sc->mt);

	clint_stop(sc);

	return (0);
}

#ifdef MDX_OF
static int
clint_get_freq(uint32_t *freq)
{
	int cpus_node;
	int error;

	cpus_node = mdx_of_node_by_path("/cpus");
	if (cpus_node < 0)
		return (MDX_ERROR);

	error = mdx_of_get_prop32(cpus_node, "timebase-frequency", freq, NULL);

	return (error);
}

#ifndef MDX_RISCV_SUPERVISOR_MODE
static int
clint_probe(mdx_device_t dev)
{

	if (!mdx_of_is_compatible(dev, "riscv,clint0"))
		return (MDX_ERROR);

	return (MDX_OK);
}

static int
clint_attach(mdx_device_t dev)
{
	struct clint_softc *sc;
	size_t base, size;
	capability cap;
	uint32_t freq;
	int error;

	if (clint_sc != NULL)
		return (MDX_EEXIST);

	sc = mdx_device_get_softc(dev);
	sc->dev = dev;

	error = mdx_of_get_reg(dev, 0, &base, &size);
	if (error)
		return (error);

	cap = mdx_getdefault();
	cap = mdx_setoffset(cap, base);
	cap = mdx_setbounds(cap, size);
	sc->base = cap;

	error = clint_get_freq(&freq);
	if (error != 0)
		return (error);

	error = clint_init(sc, cap, freq);

	return (error);
}

static struct mdx_device_ops clint_ops = {
	.probe = clint_probe,
	.attach = clint_attach,
};

static mdx_driver_t clint_driver = {
	"clint",
	&clint_ops,
	sizeof(struct clint_softc),
	clint_compat_data,
};

DRIVER_MODULE_ORDERED(clint, clint_driver, SI_ORDER_THIRD);
#else
static void
mdx_clint_sysinit(void *unused)
{
	struct clint_softc *sc;
	uint32_t freq;
	int error;

	error = clint_get_freq(&freq);
	if (error != 0) {
		printf("%s: could not get timer frequency\n", __func__);
		return;
	}

	sc = zalloc(sizeof(struct clint_softc));

	clint_init(sc, NULL, freq);
}

SYSINIT(clint, SI_SUB_DRIVERS, SI_ORDER_FIRST, mdx_clint_sysinit, NULL);
#endif
#endif