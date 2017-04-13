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

static short internal_decode_string(uint8_t *buffer, char *out_str, size_t *out_length, short *is_last_chunk)
{
	uint8_t code = buffer[0];
	size_t delta_length;
	short result;

	switch (code) {
		case 0x00: case 0x01: case 0x02: case 0x03:
		case 0x04: case 0x05: case 0x06: case 0x07:
		case 0x08: case 0x09: case 0x0a: case 0x0b:
		case 0x0c: case 0x0d: case 0x0e: case 0x0f:

		case 0x10: case 0x11: case 0x12: case 0x13:
		case 0x14: case 0x15: case 0x16: case 0x17:
		case 0x18: case 0x19: case 0x1a: case 0x1b:
		case 0x1c: case 0x1d: case 0x1e: case 0x1f:
			*is_last_chunk = 1;
			delta_length = code - 0x00;
			memcpy(out_str + *out_length, buffer + 1, delta_length);
			*out_length = *out_length + delta_length;
			return 1;

		case 0x30: case 0x31: case 0x32: case 0x33:
			*is_last_chunk = 1;
			delta_length = (code - 0x30) * 256 + buffer[1];
			memcpy(out_str + *out_length, buffer + 2, delta_length);
			*out_length = *out_length + delta_length;
			return 1;

		case 0x53:
			*is_last_chunk = 1;
			delta_length = ntohs(*(uint16_t *)(buffer + 1));
			memcpy(out_str + *out_length, buffer + 2, delta_length);
			*out_length = *out_length + delta_length;
			return 1;

		case 0x52:
			*is_last_chunk = 0;
			delta_length = ntohs(*(uint16_t *)(buffer + 1));
			memcpy(out_str + *out_length, buffer + 2, delta_length);
			*out_length = *out_length + delta_length;
			while (!*is_last_chunk) {
				result = internal_decode_string(buffer, out_str, out_length, is_last_chunk);
				if (!result) {
					return 0;
				}
			}
			break;
	}
	return 0;
}

short hessian_decode_string(uint8_t *buffer, char *out_str, size_t *out_length)
{
	short is_last_chunk = 0;
	*out_length = 0;
	return internal_decode_string(buffer, out_str, out_length, &is_last_chunk);
}
