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
#include <sys/malloc.h>
#include <sys/device.h>

extern uintptr_t __attribute((weak)) __sysinit_start;
extern uintptr_t __attribute((weak)) __sysinit_end;

void *
mdx_device_get_softc(mdx_device_t dev)
{

	return (dev->sc);
}

void *
mdx_device_alloc_softc(mdx_device_t dev, size_t size)
{

	if (dev->sc)
		return (dev->sc);

	dev->sc = malloc(size);

	return (dev->sc);
}

int
mdx_device_probe_and_attach(mdx_device_t dev)
{
	mdx_driver_t *driver;
	struct mdx_device_ops *ops;
	struct mdx_sysinit *si;
	uint8_t *start;
	uint8_t *end;
	int error;

	start = (uint8_t *)&__sysinit_start;
	end = (uint8_t *)&__sysinit_end;

	for (; start < end; start += sizeof(struct mdx_sysinit)) {
		si = (struct mdx_sysinit *)start;
		driver = si->dri;
		ops = driver->ops;
		error = ops->probe(dev);
		if (error == 0) {
			mdx_device_alloc_softc(dev, driver->size);

			error = ops->attach(dev);
			if (error != 0) {
				/* TODO: free the softc */
			}
			return (error);
		}
	}

	return (-1);
}