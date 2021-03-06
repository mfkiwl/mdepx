/*-
 * Copyright (c) 2018 Ruslan Bukin <br@bsdpad.com>
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

#ifndef _MACHINE_LIMITS_H_
#define _MACHINE_LIMITS_H_

#define	__UINT_MAX	0xffffffff
#define	__INT_MAX	0x7fffffff
#define	__USHRT_MAX	0xffff

#define	__INT_MIN	(-0x7fffffff - 1)

#define	__ULONG_MAX	0xffffffff
#define	__SIZE_T_MAX	__UINT_MAX
#define	__LONG_BIT	32

#define	__LLONG_MIN	(-0x7fffffffffffffffLL - 1)
#define	__LLONG_MAX	0x7fffffffffffffffLL
#define	__ULLONG_MAX	0xffffffffffffffffULL

#define	__LONG_MAX	0x7fffffff
#define	__LONG_MIN	(-0x7fffffff - 1)
#define	__UCHAR_MAX	0xff

#define	__CHAR_BIT	8
#define	__UQUAD_MAX	__ULLONG_MAX
#define	__QUAD_MIN	__LLONG_MIN
#define	__QUAD_MAX	__LLONG_MAX

#endif	/* !_MACHINE_LIMITS_H_ */
