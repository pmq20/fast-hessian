/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of fast-hessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#include "hessian.h"

static const size_t sublen = 0x8000;
static const uint16_t sublen_ns = 1; // htons(sublen)

short hessian_encode_string(v8::Local<v8::String> &str, uint8_t **out, size_t *len)
{
	int length = str->Length();

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
