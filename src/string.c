/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of libhessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#include "hessian.h"

size_t hessian_encode_string(char *str, size_t length, uint8_t *out)
{
	size_t strOffset = 0;
	size_t sublen;
	size_t ret = 0;
	while (length > 0x8000) {
		sublen = 0x8000;

		out[ret++] = 0x52;
		*(uint16_t *)(out + ret) = htons(sublen);
		ret += 2;
		memcpy(out + ret, str + strOffset, sublen);
		ret += sublen;

		length -= sublen;
		strOffset += sublen;
	}

	if (length <= 31) {
		out[ret++] = length;
	} else if (length <= 1023) {
		out[ret++] = 48 + (length >> 8);
		out[ret++] = length; // Integer overflow and wrapping assumed
	} else {
		out[ret++] = 'S';
		out[ret++] = (length >> 8);
		out[ret++] = length; // Integer overflow and wrapping assumed
	}

	memcpy(out + ret, str + strOffset, length - strOffset);
	ret += length - strOffset;
	return ret;
}

short hessian_decode_string(uint8_t *buffer, char *out_str, size_t *out_length)
{
	return 0;
}
