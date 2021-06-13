/*-
 * Copyright (c) 2021 Ruslan Bukin <br@bsdpad.com>
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

#ifndef	_RP2040_CLOCKS_H_
#define	_RP2040_CLOCKS_H_

#define	RP2040_CLOCKS_CLK_GPOUT0_CTRL		0x00
#define	RP2040_CLOCKS_CLK_GPOUT0_DIV		0x04
#define	RP2040_CLOCKS_CLK_GPOUT0_SELECTED	0x08
#define	RP2040_CLOCKS_CLK_GPOUT1_CTRL		0x0c
#define	RP2040_CLOCKS_CLK_GPOUT1_DIV		0x10
#define	RP2040_CLOCKS_CLK_GPOUT1_SELECTED	0x14
#define	RP2040_CLOCKS_CLK_GPOUT2_CTRL		0x18
#define	RP2040_CLOCKS_CLK_GPOUT2_DIV		0x1c
#define	RP2040_CLOCKS_CLK_GPOUT2_SELECTED	0x20
#define	RP2040_CLOCKS_CLK_GPOUT3_CTRL		0x24
#define	RP2040_CLOCKS_CLK_GPOUT3_DIV		0x28
#define	RP2040_CLOCKS_CLK_GPOUT3_SELECTED	0x2c
#define	RP2040_CLOCKS_CLK_REF_CTRL		0x30
#define	 CLOCKS_CLK_REF_CTRL_SRC_S		0
#define	 CLOCKS_CLK_REF_CTRL_SRC_M			\
		(0x3 << CLOCKS_CLK_REF_CTRL_SRC_S)
#define	 CLOCKS_CLK_REF_CTRL_SRC_ROSC_CLKSRC_PH		\
		(0x0 << CLOCKS_CLK_REF_CTRL_SRC_S)
#define	 CLOCKS_CLK_REF_CTRL_SRC_CLKSRC_CLK_REF_AUX	\
		(0x1 << CLOCKS_CLK_REF_CTRL_SRC_S)
#define	 CLOCKS_CLK_REF_CTRL_SRC_XOSC_CLKSRC		\
		(0x2 << CLOCKS_CLK_REF_CTRL_SRC_S)
#define	RP2040_CLOCKS_CLK_REF_DIV		0x34
#define	RP2040_CLOCKS_CLK_REF_SELECTED		0x38
#define	RP2040_CLOCKS_CLK_SYS_CTRL		0x3c
#define	RP2040_CLOCKS_CLK_SYS_DIV		0x40
#define	RP2040_CLOCKS_CLK_SYS_SELECTED		0x44
#define	RP2040_CLOCKS_CLK_PERI_CTRL		0x48
#define	RP2040_CLOCKS_CLK_PERI_SELECTED		0x50
#define	RP2040_CLOCKS_CLK_USB_CTRL		0x54
#define	RP2040_CLOCKS_CLK_USB_DIV		0x58
#define	RP2040_CLOCKS_CLK_USB_SELECTED		0x5c
#define	RP2040_CLOCKS_CLK_ADC_CTRL		0x60
#define	RP2040_CLOCKS_CLK_ADC_DIV		0x64
#define	RP2040_CLOCKS_CLK_ADC_SELECTED		0x68
#define	RP2040_CLOCKS_CLK_RTC_CTRL		0x6c
#define	RP2040_CLOCKS_CLK_RTC_DIV		0x70
#define	RP2040_CLOCKS_CLK_RTC_SELECTED		0x74
#define	RP2040_CLOCKS_CLK_SYS_RESUS_CTRL	0x78
#define	RP2040_CLOCKS_CLK_SYS_RESUS_STATUS	0x7c
#define	RP2040_CLOCKS_FC0_REF_KHZ		0x80
#define	RP2040_CLOCKS_FC0_MIN_KHZ		0x84
#define	RP2040_CLOCKS_FC0_MAX_KHZ		0x88
#define	RP2040_CLOCKS_FC0_DELAY			0x8c
#define	RP2040_CLOCKS_FC0_INTERVAL		0x90
#define	RP2040_CLOCKS_FC0_SRC			0x94
#define	RP2040_CLOCKS_FC0_STATUS		0x98
#define	RP2040_CLOCKS_FC0_RESULT		0x9c
#define	RP2040_CLOCKS_WAKE_EN0			0xa0
#define	RP2040_CLOCKS_WAKE_EN1			0xa4
#define	RP2040_CLOCKS_SLEEP_EN0			0xa8
#define	RP2040_CLOCKS_SLEEP_EN1			0xac
#define	RP2040_CLOCKS_ENABLED0			0xb0
#define	RP2040_CLOCKS_ENABLED1			0xb4
#define	RP2040_CLOCKS_INTR			0xb8
#define	RP2040_CLOCKS_INTE			0xbc
#define	RP2040_CLOCKS_INTF			0xc0
#define	RP2040_CLOCKS_INTS			0xc4

struct rp2040_clocks_softc {
	uint32_t base;
};

void rp2040_clocks_init(struct rp2040_clocks_softc *sc, uint32_t base);

#endif /* !_RP2040_CLOCKS_H_ */