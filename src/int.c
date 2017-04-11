/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of libhessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#include "hessian.h"

#define INT_DIRECT_MIN -0x10
#define INT_DIRECT_MAX 0x2f
#define INT_ZERO 0x90

#define INT_BYTE_MIN -0x800
#define INT_BYTE_MAX 0x7ff
#define INT_BYTE_ZERO 0xc8

#define INT_SHORT_MIN -0x40000
#define INT_SHORT_MAX 0x3ffff
#define INT_SHORT_ZERO 0xd4

uint32_t hessian_decode_int(uint8_t *buffer)
{
	return 0;
}

size_t hessian_encode_int(uint32_t val, uint8_t *out)
{
	if (INT_DIRECT_MIN <= val && val <= INT_DIRECT_MAX) {
		out[0] = val + INT_ZERO;
		return 1;
	} else if (INT_BYTE_MIN <= val && val <= INT_BYTE_MAX) {
		out[1] = val & 0xff;
		out[0] = (val >> 8) + INT_BYTE_ZERO;
		return 2;
	} else if (INT_SHORT_MIN <= val && val <= INT_SHORT_MAX) {
		*(uint16_t *)(out) = val & 0xffff;
		out[2] = (val >> 16) + INT_SHORT_ZERO;
		return 3;
	} else {
		out[0] = 'I';
		*(uint32_t *)(out+1) = val;
		return 5;
	}
}
