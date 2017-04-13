/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of libhessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#include "hessian.h"

short hessian_decode_long(uint8_t *buffer, uint64_t *out)
{
	uint8_t code = buffer[0];
	if (code >= 0xd8 && code <= 0xef) {
		*out = code - 0xe0;
		return 1;
	}
	if (code >= 0xf0 && code <= 0xff) {
		*out = ((code - 0xf8) << 8) + out[1];
		return 1;
	}
	if (code >= 0x38 && code <= 0x3f) {
		*out =((code - 0x3c) << 16) + (out[1] << 8) + out[2];
		return 1;
	}
	if (code == 0x59) {
		*out = ntohl(*(int32_t *)(buffer+1));
		return 1;
	}
	if (code == 0x4c) {
		*out = ntohll(*(uint64_t *)(buffer + 1));
		return 1;
	}
	return 0;
}

size_t hessian_encode_long(uint64_t val, uint8_t *out)
{
	if (val >= -8 && val <= 15) {
		out[0] = val + 0xe0;
		return 1;
        } else if (val >= -2048 && val <= 2047) {
		out[0] = (val >> 8) + 0xf8;
		out[1] = val & 0xff;
		return 2;
        } else if (val >= -262144 && val <= 262143) {
		out[0] = (val >> 16) + 0x3c;
		*(uint16_t *)(out + 1) = htons(val & 0xffff);
		return 3;
        } else if (val >= -0x80000000 && val <= 0x7fffffff) {
		out[0] = 0x59;
		*(int32_t *)(out + 1) = htons((int32_t)val);
		return 5;
	} else {
		out[0] = 0x4c;
		*(int64_t *)(out + 1) = htonll(val);
		return 9;
	}
}
