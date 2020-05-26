/*-
 * Copyright (c) 2018-2020 Ruslan Bukin <br@bsdpad.com>
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
#include <sys/of.h>
#include <sys/callout.h>
#include <sys/systm.h>
#include <sys/malloc.h>
#include <sys/thread.h>

#include <arm/arm/nvic.h>
#include <arm/nordicsemi/nrf5340_app_core.h>

#include <dev/intc/intc.h>

#include "board.h"

struct mdx_device dev_nvic;
struct arm_nvic_softc nvic_sc;

struct nrf_uarte_softc uarte_sc;
struct nrf_spu_softc spu_sc;
struct nrf_power_softc power_sc;
struct nrf_timer_softc timer0_sc;
struct nrf_rtc_softc rtc_sc;

void
board_init(void)
{

	mdx_fl_init();
	mdx_fl_add_region(0x20021000, 0x1f000);

	mdx_of_install_dtbp((void *)0xf8000);
	mdx_of_probe_devices();

#if 0
	nrf_uarte_init(&uarte_sc, BASE_UARTE0,
	    UART_PIN_TX, UART_PIN_RX, UART_BAUDRATE);
	mdx_console_register(uart_putchar, (void *)&uarte_sc);
	nrf_uarte_register_callback(&uarte_sc, nrf_input, NULL);

	nrf_power_init(&power_sc, BASE_POWER);
	nrf_rtc_init(&rtc_sc, BASE_RTC1, 0 /* prescaler */);
	nrf_timer_init(&timer0_sc, BASE_TIMER0, 1000000);
	arm_nvic_init(&dev_nvic, &nvic_sc, BASE_SCS);

	mdx_intc_setup(&dev_nvic, ID_UARTE0, nrf_uarte_intr, &uarte_sc);
	mdx_intc_setup(&dev_nvic, ID_TIMER0, nrf_timer_intr, &timer0_sc);
	mdx_intc_setup(&dev_nvic, ID_RTC1,   nrf_rtc_intr,   &rtc_sc);

	mdx_intc_set_prio(&dev_nvic, ID_IPC, 6);

	mdx_intc_enable(&dev_nvic, ID_TIMER0);
	mdx_intc_enable(&dev_nvic, ID_UARTE0);
	mdx_intc_enable(&dev_nvic, ID_IPC);
	mdx_intc_enable(&dev_nvic, ID_RTC1);

	mdx_clock_register(CLOCK_REALTIME, &nrf_rtc_driver, &rtc_sc);
#endif

	printf("mdepx initialized\n");
}
