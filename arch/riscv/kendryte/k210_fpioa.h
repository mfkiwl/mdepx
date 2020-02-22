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

#ifndef	_RISCV_KENDRYTE_K210_FPIOA_H_
#define	_RISCV_KENDRYTE_K210_FPIOA_H_

#define	FPIOA_FUNC_JTAG_TCLK		0
#define	FPIOA_FUNC_JTAG_TDI		1
#define	FPIOA_FUNC_JTAG_TMS		2
#define	FPIOA_FUNC_JTAG_TDO		3
#define	FPIOA_FUNC_SPI0_D0		4
#define	FPIOA_FUNC_SPI0_D1		5
#define	FPIOA_FUNC_SPI0_D2		6
#define	FPIOA_FUNC_SPI0_D3		7
#define	FPIOA_FUNC_SPI0_D4		8
#define	FPIOA_FUNC_SPI0_D5		9
#define	FPIOA_FUNC_SPI0_D6		10
#define	FPIOA_FUNC_SPI0_D7		11
#define	FPIOA_FUNC_SPI0_SS0		12
#define	FPIOA_FUNC_SPI0_SS1		13
#define	FPIOA_FUNC_SPI0_SS2		14
#define	FPIOA_FUNC_SPI0_SS3		15
#define	FPIOA_FUNC_SPI0_ARB		16
#define	FPIOA_FUNC_SPI0_SCLK		17
#define	FPIOA_FUNC_UARTHS_RX		18
#define	FPIOA_FUNC_UARTHS_TX		19
#define	FPIOA_FUNC_RESV6		20
#define	FPIOA_FUNC_RESV7		21
#define	FPIOA_FUNC_CLK_SPI1		22
#define	FPIOA_FUNC_CLK_I2C1		23
#define	FPIOA_FUNC_GPIOHS0		24
#define	FPIOA_FUNC_GPIOHS1		25
#define	FPIOA_FUNC_GPIOHS2		26
#define	FPIOA_FUNC_GPIOHS3		27
#define	FPIOA_FUNC_GPIOHS4		28
#define	FPIOA_FUNC_GPIOHS5		29
#define	FPIOA_FUNC_GPIOHS6		30
#define	FPIOA_FUNC_GPIOHS7		31
#define	FPIOA_FUNC_GPIOHS8		32
#define	FPIOA_FUNC_GPIOHS9		33
#define	FPIOA_FUNC_GPIOHS10		34
#define	FPIOA_FUNC_GPIOHS11		35
#define	FPIOA_FUNC_GPIOHS12		36
#define	FPIOA_FUNC_GPIOHS13		37
#define	FPIOA_FUNC_GPIOHS14		38
#define	FPIOA_FUNC_GPIOHS15		39
#define	FPIOA_FUNC_GPIOHS16		40
#define	FPIOA_FUNC_GPIOHS17		41
#define	FPIOA_FUNC_GPIOHS18		42
#define	FPIOA_FUNC_GPIOHS19		43
#define	FPIOA_FUNC_GPIOHS20		44
#define	FPIOA_FUNC_GPIOHS21		45
#define	FPIOA_FUNC_GPIOHS22		46
#define	FPIOA_FUNC_GPIOHS23		47
#define	FPIOA_FUNC_GPIOHS24		48
#define	FPIOA_FUNC_GPIOHS25		49
#define	FPIOA_FUNC_GPIOHS26		50
#define	FPIOA_FUNC_GPIOHS27		51
#define	FPIOA_FUNC_GPIOHS28		52
#define	FPIOA_FUNC_GPIOHS29		53
#define	FPIOA_FUNC_GPIOHS30		54
#define	FPIOA_FUNC_GPIOHS31		55
#define	FPIOA_FUNC_GPIO0		56
#define	FPIOA_FUNC_GPIO1		57
#define	FPIOA_FUNC_GPIO2		58
#define	FPIOA_FUNC_GPIO3		59
#define	FPIOA_FUNC_GPIO4		60
#define	FPIOA_FUNC_GPIO5		61
#define	FPIOA_FUNC_GPIO6		62
#define	FPIOA_FUNC_GPIO7		63
#define	FPIOA_FUNC_UART1_RX		64
#define	FPIOA_FUNC_UART1_TX		65
#define	FPIOA_FUNC_UART2_RX		66
#define	FPIOA_FUNC_UART2_TX		67
#define	FPIOA_FUNC_UART3_RX		68
#define	FPIOA_FUNC_UART3_TX		69
#define	FPIOA_FUNC_SPI1_D0		70
#define	FPIOA_FUNC_SPI1_D1		71
#define	FPIOA_FUNC_SPI1_D2		72
#define	FPIOA_FUNC_SPI1_D3		73
#define	FPIOA_FUNC_SPI1_D4		74
#define	FPIOA_FUNC_SPI1_D5		75
#define	FPIOA_FUNC_SPI1_D6		76
#define	FPIOA_FUNC_SPI1_D7		77
#define	FPIOA_FUNC_SPI1_SS0		78
#define	FPIOA_FUNC_SPI1_SS1		79
#define	FPIOA_FUNC_SPI1_SS2		80
#define	FPIOA_FUNC_SPI1_SS3		81
#define	FPIOA_FUNC_SPI1_ARB		82
#define	FPIOA_FUNC_SPI1_SCLK		83
#define	FPIOA_FUNC_SPI_SLAVE_D0		84
#define	FPIOA_FUNC_SPI_SLAVE_SS		85
#define	FPIOA_FUNC_SPI_SLAVE_SCLK	86
#define	FPIOA_FUNC_I2S0_MCLK		87
#define	FPIOA_FUNC_I2S0_SCLK		88
#define	FPIOA_FUNC_I2S0_WS		89
#define	FPIOA_FUNC_I2S0_IN_D0		90
#define	FPIOA_FUNC_I2S0_IN_D1		91
#define	FPIOA_FUNC_I2S0_IN_D2		92
#define	FPIOA_FUNC_I2S0_IN_D3		93
#define	FPIOA_FUNC_I2S0_OUT_D0		94
#define	FPIOA_FUNC_I2S0_OUT_D1		95
#define	FPIOA_FUNC_I2S0_OUT_D2		96
#define	FPIOA_FUNC_I2S0_OUT_D3		97
#define	FPIOA_FUNC_I2S1_MCLK		98
#define	FPIOA_FUNC_I2S1_SCLK		99
#define	FPIOA_FUNC_I2S1_WS		100
#define	FPIOA_FUNC_I2S1_IN_D0		101
#define	FPIOA_FUNC_I2S1_IN_D1		102
#define	FPIOA_FUNC_I2S1_IN_D2		103
#define	FPIOA_FUNC_I2S1_IN_D3		104
#define	FPIOA_FUNC_I2S1_OUT_D0		105
#define	FPIOA_FUNC_I2S1_OUT_D1		106
#define	FPIOA_FUNC_I2S1_OUT_D2		107
#define	FPIOA_FUNC_I2S1_OUT_D3		108
#define	FPIOA_FUNC_I2S2_MCLK		109
#define	FPIOA_FUNC_I2S2_SCLK		110
#define	FPIOA_FUNC_I2S2_WS		111
#define	FPIOA_FUNC_I2S2_IN_D0		112
#define	FPIOA_FUNC_I2S2_IN_D1		113
#define	FPIOA_FUNC_I2S2_IN_D2		114
#define	FPIOA_FUNC_I2S2_IN_D3		115
#define	FPIOA_FUNC_I2S2_OUT_D0		116
#define	FPIOA_FUNC_I2S2_OUT_D1		117
#define	FPIOA_FUNC_I2S2_OUT_D2		118
#define	FPIOA_FUNC_I2S2_OUT_D3		119
#define	FPIOA_FUNC_RESV0		120
#define	FPIOA_FUNC_RESV1		121
#define	FPIOA_FUNC_RESV2		122
#define	FPIOA_FUNC_RESV3		123
#define	FPIOA_FUNC_RESV4		124
#define	FPIOA_FUNC_RESV5		125
#define	FPIOA_FUNC_I2C0_SCLK		126
#define	FPIOA_FUNC_I2C0_SDA		127
#define	FPIOA_FUNC_I2C1_SCLK		128
#define	FPIOA_FUNC_I2C1_SDA		129
#define	FPIOA_FUNC_I2C2_SCLK		130
#define	FPIOA_FUNC_I2C2_SDA		131
#define	FPIOA_FUNC_CMOS_XCLK		132
#define	FPIOA_FUNC_CMOS_RST		133
#define	FPIOA_FUNC_CMOS_PWDN		134
#define	FPIOA_FUNC_CMOS_VSYNC		135
#define	FPIOA_FUNC_CMOS_HREF		136
#define	FPIOA_FUNC_CMOS_PCLK		137
#define	FPIOA_FUNC_CMOS_D0		138
#define	FPIOA_FUNC_CMOS_D1		139
#define	FPIOA_FUNC_CMOS_D2		140
#define	FPIOA_FUNC_CMOS_D3		141
#define	FPIOA_FUNC_CMOS_D4		142
#define	FPIOA_FUNC_CMOS_D5		143
#define	FPIOA_FUNC_CMOS_D6		144
#define	FPIOA_FUNC_CMOS_D7		145
#define	FPIOA_FUNC_SCCB_SCLK		146
#define	FPIOA_FUNC_SCCB_SDA		147
#define	FPIOA_FUNC_UART1_CTS		148
#define	FPIOA_FUNC_UART1_DSR		149
#define	FPIOA_FUNC_UART1_DCD		150
#define	FPIOA_FUNC_UART1_RI		151
#define	FPIOA_FUNC_UART1_SIR_IN		152
#define	FPIOA_FUNC_UART1_DTR		153
#define	FPIOA_FUNC_UART1_RTS		154
#define	FPIOA_FUNC_UART1_OUT2		155
#define	FPIOA_FUNC_UART1_OUT1		156
#define	FPIOA_FUNC_UART1_SIR_OUT	157
#define	FPIOA_FUNC_UART1_BAUD		158
#define	FPIOA_FUNC_UART1_RE		159
#define	FPIOA_FUNC_UART1_DE		160
#define	FPIOA_FUNC_UART1_RS485_EN	161
#define	FPIOA_FUNC_UART2_CTS		162
#define	FPIOA_FUNC_UART2_DSR		163
#define	FPIOA_FUNC_UART2_DCD		164
#define	FPIOA_FUNC_UART2_RI		165
#define	FPIOA_FUNC_UART2_SIR_IN		166
#define	FPIOA_FUNC_UART2_DTR		167
#define	FPIOA_FUNC_UART2_RTS		168
#define	FPIOA_FUNC_UART2_OUT2		169
#define	FPIOA_FUNC_UART2_OUT1		170
#define	FPIOA_FUNC_UART2_SIR_OUT	171
#define	FPIOA_FUNC_UART2_BAUD		172
#define	FPIOA_FUNC_UART2_RE		173
#define	FPIOA_FUNC_UART2_DE		174
#define	FPIOA_FUNC_UART2_RS485_EN	175
#define	FPIOA_FUNC_UART3_CTS		176
#define	FPIOA_FUNC_UART3_DSR		177
#define	FPIOA_FUNC_UART3_DCD		178
#define	FPIOA_FUNC_UART3_RI		179
#define	FPIOA_FUNC_UART3_SIR_IN		180
#define	FPIOA_FUNC_UART3_DTR		181
#define	FPIOA_FUNC_UART3_RTS		182
#define	FPIOA_FUNC_UART3_OUT2		183
#define	FPIOA_FUNC_UART3_OUT1		184
#define	FPIOA_FUNC_UART3_SIR_OUT	185
#define	FPIOA_FUNC_UART3_BAUD		186
#define	FPIOA_FUNC_UART3_RE		187
#define	FPIOA_FUNC_UART3_DE		188
#define	FPIOA_FUNC_UART3_RS485_EN	189
#define	FPIOA_FUNC_TIMER0_TOGGLE1	190
#define	FPIOA_FUNC_TIMER0_TOGGLE2	191
#define	FPIOA_FUNC_TIMER0_TOGGLE3	192
#define	FPIOA_FUNC_TIMER0_TOGGLE4	193
#define	FPIOA_FUNC_TIMER1_TOGGLE1	194
#define	FPIOA_FUNC_TIMER1_TOGGLE2	195
#define	FPIOA_FUNC_TIMER1_TOGGLE3	196
#define	FPIOA_FUNC_TIMER1_TOGGLE4	197
#define	FPIOA_FUNC_TIMER2_TOGGLE1	198
#define	FPIOA_FUNC_TIMER2_TOGGLE2	199
#define	FPIOA_FUNC_TIMER2_TOGGLE3	200
#define	FPIOA_FUNC_TIMER2_TOGGLE4	201
#define	FPIOA_FUNC_CLK_SPI2		202
#define	FPIOA_FUNC_CLK_I2C2		203
#define	FPIOA_FUNC_INTERNAL0		204
#define	FPIOA_FUNC_INTERNAL1		205
#define	FPIOA_FUNC_INTERNAL2		206
#define	FPIOA_FUNC_INTERNAL3		207
#define	FPIOA_FUNC_INTERNAL4		208
#define	FPIOA_FUNC_INTERNAL5		209
#define	FPIOA_FUNC_INTERNAL6		210
#define	FPIOA_FUNC_INTERNAL7		211
#define	FPIOA_FUNC_INTERNAL8		212
#define	FPIOA_FUNC_INTERNAL9		213
#define	FPIOA_FUNC_INTERNAL10		214
#define	FPIOA_FUNC_INTERNAL11		215
#define	FPIOA_FUNC_INTERNAL12		216
#define	FPIOA_FUNC_INTERNAL13		217
#define	FPIOA_FUNC_INTERNAL14		218
#define	FPIOA_FUNC_INTERNAL15		219
#define	FPIOA_FUNC_INTERNAL16		220
#define	FPIOA_FUNC_INTERNAL17		221
#define	FPIOA_FUNC_CONSTANT		222
#define	FPIOA_FUNC_INTERNAL18		223
#define	FPIOA_FUNC_DEBUG0		224
#define	FPIOA_FUNC_DEBUG1		225
#define	FPIOA_FUNC_DEBUG2		226
#define	FPIOA_FUNC_DEBUG3		227
#define	FPIOA_FUNC_DEBUG4		228
#define	FPIOA_FUNC_DEBUG5		229
#define	FPIOA_FUNC_DEBUG6		230
#define	FPIOA_FUNC_DEBUG7		231
#define	FPIOA_FUNC_DEBUG8		232
#define	FPIOA_FUNC_DEBUG9		233
#define	FPIOA_FUNC_DEBUG10		234
#define	FPIOA_FUNC_DEBUG11		235
#define	FPIOA_FUNC_DEBUG12		236
#define	FPIOA_FUNC_DEBUG13		237
#define	FPIOA_FUNC_DEBUG14		238
#define	FPIOA_FUNC_DEBUG15		239
#define	FPIOA_FUNC_DEBUG16		240
#define	FPIOA_FUNC_DEBUG17		241
#define	FPIOA_FUNC_DEBUG18		242
#define	FPIOA_FUNC_DEBUG19		243
#define	FPIOA_FUNC_DEBUG20		244
#define	FPIOA_FUNC_DEBUG21		245
#define	FPIOA_FUNC_DEBUG22		246
#define	FPIOA_FUNC_DEBUG23		247
#define	FPIOA_FUNC_DEBUG24		248
#define	FPIOA_FUNC_DEBUG25		249
#define	FPIOA_FUNC_DEBUG26		250
#define	FPIOA_FUNC_DEBUG27		251
#define	FPIOA_FUNC_DEBUG28		252
#define	FPIOA_FUNC_DEBUG29		253
#define	FPIOA_FUNC_DEBUG30		254
#define	FPIOA_FUNC_DEBUG31		255

struct fpioa_io_config { 
	uint32_t ch_sel	:8;
	uint32_t ds	:4;	/* Drive */
	uint32_t oe_en	:1;	/* Output Enable */
	uint32_t oe_inv	:1;
	uint32_t do_sel	:1;
	uint32_t do_inv	:1;
	uint32_t pu	:1;
	uint32_t pd	:1;
	uint32_t resv0	:1;
	uint32_t sl	:1;
	uint32_t ie_en	:1;	/* Input Enable */
	uint32_t ie_inv	:1;
	uint32_t di_inv	:1;
	uint32_t st	:1;
	uint32_t resv1	:7;
	uint32_t pad_di	:1;
};

struct k210_fpioa_softc {
	size_t base;
};

void k210_fpioa_init(struct k210_fpioa_softc *sc, uint32_t base);
void k210_fpioa_set_config(struct k210_fpioa_softc *sc,
    uint32_t number, struct fpioa_io_config *cfg);

#endif /* !_RISCV_KENDRYTE_K210_FPIOA_H_ */