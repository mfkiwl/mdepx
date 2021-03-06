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

#include <riscv/kendryte/k210_sysctl.h>

#define	RD4(_sc, _reg)		\
	*(volatile uint32_t *)((_sc)->base + _reg)
#define	WR4(_sc, _reg, _val)	\
	*(volatile uint32_t *)((_sc)->base + _reg) = _val

void
k210_sysctl_init(struct k210_sysctl_softc *sc, uint32_t base)
{
	uint32_t reg;

	sc->base = base;

	reg = RD4(sc, K210_SYSCTL_CLK_EN_CENT);
	reg |= CENT_CLK_EN_APB0;
	reg |= CENT_CLK_EN_APB1;
	reg |= CENT_CLK_EN_APB2;
	WR4(sc, K210_SYSCTL_CLK_EN_CENT, reg);

	reg = RD4(sc, K210_SYSCTL_CLK_EN_PERI);
	reg |= PERI_CLK_EN_GPIO;
	reg |= PERI_CLK_EN_UART1;
	reg |= PERI_CLK_EN_UART2;
	reg |= PERI_CLK_EN_UART3;
	reg |= PERI_CLK_EN_I2C0;
	reg |= PERI_CLK_EN_I2C1;
	reg |= PERI_CLK_EN_I2C2;
	reg |= PERI_CLK_EN_FPIOA;
	WR4(sc, K210_SYSCTL_CLK_EN_PERI, reg);
}
