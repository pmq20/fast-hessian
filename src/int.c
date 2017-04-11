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

int32_t hessian_decode_int(uint8_t *buffer)
{
	uint8_t code = buffer[0];
	// Compact int
	if (code >= 0x80 && code <= 0xbf) {
		// Integers between -16 and 47 can be encoded by a single octet in the range x80 to xbf.
		// value = code - 0x90
		return code - 0x90;
	}
	if (code >= 0xc0 && code <= 0xcf) {
		// Integers between -2048 and 2047 can be encoded in two octets with the leading byte in the range xc0 to xcf.
		// value = ((code - 0xc8) << 8) + b0;
		return ((code - 0xc8) << 8) + buffer[1];
	}
	if (code >= 0xd0 && code <= 0xd7) {
		// Integers between -262144 and 262143 can be encoded in three bytes with the leading byte in the range xd0 to xd7.
		// value = ((code - 0xd4) << 16) + (b1 << 8) + b0;
		return ((code - 0xd4) << 16) + (buffer[1] << 8) + buffer[2];
	}
	if (code == 0x49) {
		return ntohl(*(int32_t *)(buffer+1));
	}
	assert(0);
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
		*(int16_t *)(out + 1) = htons(val & 0xffff);
		return 3;
	} else {
		out[0] = 0x49;
		*(int32_t *)(out+1) = htonl(val);
		return 5;
	}
}
