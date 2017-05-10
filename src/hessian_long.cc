/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of fast-hessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#include "hessian.h"

short hessian_decode_long(uint8_t * const buf, const size_t buf_length, const v8::FunctionCallbackInfo<v8::Value>& args)
{
	uint8_t code = buf[0];
	if (code >= 0xd8 && code <= 0xef) {
		args.GetReturnValue().Set(code - 0xe0);
		return 1;
	}
	if (buf_length >= 2 && code >= 0xf0 && code <= 0xff) {
		args.GetReturnValue().Set(((code - 0xf8) << 8) + buf[1]);
		return 1;
	}
	if (buf_length >= 3 && code >= 0x38 && code <= 0x3f) {
		args.GetReturnValue().Set(((code - 0x3c) << 16) + (buf[1] << 8) + buf[2]);
		return 1;
	}
	if (buf_length >= 4 && code == 0x59) {
		args.GetReturnValue().Set(static_cast<uint32_t>(ntohl(*(int32_t *)(buf+1))));
		return 1;
	}
	if (buf_length >= 5 && code == 0x4c) {
		args.GetReturnValue().Set((double)(ntohll(*(int64_t *)(buf + 1))));
		return 1;
	}
	return 0;
}

short hessian_encode_long(int64_t val, uint8_t **out, size_t *len)
{
	if (val >= -8 && val <= 15) {
		*len = 1;
		*out = (uint8_t*)malloc(*len);
		if (NULL == *out) {
			return 0;
		}
		*out[0] = (uint8_t)(val + 0xe0);
		return 1;
	} else if (val >= -2048 && val <= 2047) {
		*len = 2;
		*out = (uint8_t*)malloc(*len);
		if (NULL == *out) {
			return 0;
		}
		*out[0] = (uint8_t)((val >> 8) + 0xf8);
		*out[1] = (uint8_t)(val & 0xff);
		return 1;
	} else if (val >= -262144 && val <= 262143) {
		*len = 3;
		*out = (uint8_t*)malloc(*len);
		if (NULL == *out) {
			return 0;
		}
		*out[0] = (uint8_t)((val >> 16) + 0x3c);
		*(uint16_t *)(*out + 1) = htons(val & 0xffff);
		return 1;
	} else if (val >= -0x80000000LL && val <= 0x7fffffffLL) {
		*len = 5;
		*out = (uint8_t*)malloc(*len);
		if (NULL == *out) {
			return 0;
		}
		*out[0] = 0x59;
		*(int32_t *)(*out + 1) = htons((int32_t)val);
		return 1;
	} else {
		*len = 9;
		*out = (uint8_t*)malloc(*len);
		if (NULL == *out) {
			return 0;
		}
		*out[0] = 0x4c;
		*(int64_t *)(*out + 1) = htonll(val);
		return 1;
	}
}
