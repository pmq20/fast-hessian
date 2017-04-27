/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of libhessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#include "hessian.h"
#include "hessian-impl.h"

#define INT_DIRECT_MIN -0x10
#define INT_DIRECT_MAX 0x2f
#define INT_ZERO 0x90

#define INT_BYTE_MIN -0x800
#define INT_BYTE_MAX 0x7ff
#define INT_BYTE_ZERO 0xc8

#define INT_SHORT_MIN -0x40000
#define INT_SHORT_MAX 0x3ffff
#define INT_SHORT_ZERO 0xd4

short hessian_decode_int(uint8_t *buffer, int32_t *out)
{
	uint8_t code = buffer[0];
	if (code >= 0x80 && code <= 0xbf) {
		*out = code - 0x90;
		return 1;
	}
	if (code >= 0xc0 && code <= 0xcf) {
		*out = ((code - 0xc8) << 8) + buffer[1];
		return 1;
	}
	if (code >= 0xd0 && code <= 0xd7) {
		*out = ((code - 0xd4) << 16) + (buffer[1] << 8) + buffer[2];
		return 1;
	}
	if (code == 0x49) {
		*out = ntohl(*(int32_t *)(buffer+1));
		return 1;
	}
	return 0;
}

size_t hessian_encode_int(int32_t val, uint8_t *out)
{
	if (INT_DIRECT_MIN <= val && val <= INT_DIRECT_MAX) {
		out[0] = val + INT_ZERO;
		return 1;
	} else if (INT_BYTE_MIN <= val && val <= INT_BYTE_MAX) {
		out[1] = val & 0xff;
		out[0] = (val >> 8) + INT_BYTE_ZERO;
		return 2;
	} else if (INT_SHORT_MIN <= val && val <= INT_SHORT_MAX) {
		out[0] = (val >> 16) + INT_SHORT_ZERO;
		*(uint16_t *)(out + 1) = htons(val & 0xffff);
		return 3;
	} else {
		out[0] = 0x49;
		*(int32_t *)(out+1) = htonl(val);
		return 5;
	}
}
