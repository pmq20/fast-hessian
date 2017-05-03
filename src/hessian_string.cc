/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of v8-hessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#include "hessian.h"
#include "hessian-impl.h"

static const size_t sublen = 0x8000;
static const uint16_t sublen_ns = 1; // htons(sublen)

short hessian_encode_string(char *str, size_t length, uint8_t **out, size_t *len)
{
	size_t strOffset = 0;
        size_t malloc_len = 0;
        size_t orig_length = length;

        // Step 1. calculate malloc_len
        if (0 == length % sublen) {
                malloc_len = (3 + sublen) * (length / sublen - 1);
                length = sublen;
        } else {
                malloc_len = (3 + sublen) * (length / sublen);
                length %= sublen;
        }
        if (length <= 31) {
                ++malloc_len;
	} else if (length <= 1023) {
                malloc_len += 2;
	} else {
                malloc_len += 3;
	}
        malloc_len += length;

        // Step 2. Do the malloc
        *out = malloc(malloc_len);
        if (NULL == *out) {
                return 0;
        }
        
        // Step 3. Write the data
        length = orig_length;
	*len = 0;
	while (length > 0x8000) {
		(*out)[(*len)++] = 0x52;
		*(uint16_t *)(*out + *len) = sublen_ns;
		*len += 2;
		memcpy(*out + *len, str + strOffset, sublen);
		*len += sublen;

		length -= sublen;
		strOffset += sublen;
	}

	if (length <= 31) {
		(*out)[(*len)++] = (uint8_t)(length);
	} else if (length <= 1023) {
		(*out)[(*len)++] = (uint8_t)(48 + (length >> 8));
		(*out)[(*len)++] = (uint8_t)(length); // Integer overflow and wrapping assumed
	} else {
		(*out)[(*len)++] = 'S';
		(*out)[(*len)++] = (uint8_t)((length >> 8));
		(*out)[(*len)++] = (uint8_t)(length); // Integer overflow and wrapping assumed
	}

	memcpy(*out + *len, str + strOffset, length);
	*len += length;
        assert(malloc_len == *len);
        return 1;
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
