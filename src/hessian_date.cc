/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of v8-hessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#include "hessian.h"

short hessian_decode_date(uint8_t *buffer, uint64_t *out)
{
	uint8_t code = buffer[0];
	if (code == 0x4a) {
		*out = ntohll(*(uint64_t *)(buffer + 1));
		return 1;
	}
	if (code == 0x4b) {
		*out = ntohl(*(uint32_t *)(buffer + 1)) * 60000;
		return 1;
	}
	return 0;
}

short hessian_encode_date(uint64_t milliEpoch, uint8_t **out, size_t *len)
{
	if ((milliEpoch % 60000) == 0) {
		uint64_t minutes = milliEpoch / 60000;
		if (minutes <= 0x7fffffff) {
			*len = 5;
                        *out = (uint8_t*)malloc(*len);
                        if (NULL == *out) {
                                return 0;
                        }
			*out[0] = 0x4b;
			*(int32_t *)(*out + 1) = htonl((uint32_t)minutes);
                        return 1;
		}
	}
	*len = 9;
        *out = (uint8_t*)malloc(*len);
        if (NULL == *out) {
                return 0;
        }
	*out[0] = 0x4a;
	*(int64_t *)(*out + 1) = htonll(milliEpoch);
        return 1;
}
