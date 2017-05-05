/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of fast-hessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#include "hessian.h"

short hessian_encode_string(v8::Local<v8::String> &str, uint8_t **out, size_t *len)
{
	size_t index = 0;
	int length = str->Length();
	int capacity = 3 * length + 10; // TODO 10?
	*out = (uint8_t*)malloc(capacity);
	if (NULL == *out) {
		return 0;
	}

	// TODO
	assert(length <= 0x8000);

	if (length <= 31) {
		(*out)[index++] = (uint8_t)(length);
	} else if (length <= 1023) {
		(*out)[index++] = (uint8_t)(48 + (length >> 8));
		// Integer overflow and wrapping assumed
		(*out)[index++] = (uint8_t)(length);
	} else {
		(*out)[index++] = 'S';
		(*out)[index++] = (uint8_t)((length >> 8));
		// Integer overflow and wrapping assumed
		(*out)[index++] = (uint8_t)(length);
	}

	// TODO encoded as CESU-8
	int flags = v8::String::HINT_MANY_WRITES_EXPECTED | v8::String::NO_NULL_TERMINATION | v8::String::REPLACE_INVALID_UTF8;
	int nbytes = str->WriteUtf8((char *)(*out + index), capacity, NULL, flags);
	*len = index + nbytes;
	uint8_t *new_out = (uint8_t*)realloc(*out, *len);
	if (NULL != new_out) {
		*out = new_out;
	}
	return 1;
}

static short internal_decode_string(uint8_t * const buf, const size_t buf_length, uint8_t *out_str, size_t *out_length, short *is_last_chunk)
{
	uint8_t code = buf[0];
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
			if (buf_length < 1 + delta_length) {
				return 0;
			}
			memcpy(out_str + *out_length, buf + 1, delta_length);
			*out_length = *out_length + delta_length;
			return 1;

		case 0x30: case 0x31: case 0x32: case 0x33:
			*is_last_chunk = 1;
			if (buf_length < 2) {
				return 0;
			}
			delta_length = (code - 0x30) * 256 + buf[1];
			if (buf_length < 2 + delta_length) {
				return 0;
			}
			memcpy(out_str + *out_length, buf + 2, delta_length);
			*out_length = *out_length + delta_length;
			return 1;

		case 0x53:
			*is_last_chunk = 1;
			if (buf_length < 3) {
				return 0;
			}
			delta_length = ntohs(*(uint16_t *)(buf + 1));
			if (buf_length < 3 + delta_length) {
				return 0;
			}
			memcpy(out_str + *out_length, buf + 3, delta_length);
			*out_length = *out_length + delta_length;
			return 1;

		case 0x52:
			*is_last_chunk = 0;
			if (buf_length < 3) {
				return 0;
			}
			delta_length = ntohs(*(uint16_t *)(buf + 1));
			if (buf_length < 3 + delta_length) {
				return 0;
			}
			memcpy(out_str + *out_length, buf + 3, delta_length);
			*out_length = *out_length + delta_length;
			while (!*is_last_chunk) {
				result = internal_decode_string(buf, buf_length, out_str, out_length, is_last_chunk);
				if (!result) {
					return 0;
				}
			}
			break;
	}
	return 0;
}

class HessianExternalOneByteStringResource : public v8::ExternalOneByteStringResource
{
public:
	HessianExternalOneByteStringResource(uint8_t *out_str, size_t out_length)
		: out_str_(out_str), out_length_(out_length) {}
	~HessianExternalOneByteStringResource() { free(out_str_); }

	const char* data() const { return out_str_; }
	size_t length() const { return out_length_; }
private:
	const char* out_str_;
	size_t out_length_;
};

short hessian_decode_string(uint8_t * const buf, const size_t buf_length, const v8::FunctionCallbackInfo<v8::Value>& args)
{
	node::Environment* env = node::Environment::GetCurrent(args);
	EscapableHandleScope scope(env->isolate());
	v8::Local<v8::String> string;
	short is_last_chunk = 0;
	size_t out_length = 0;
	uint8_t *out_str = (uint8_t *)malloc(buf_length);
	if (NULL == out_str) {
		return 0;
	}
	if (internal_decode_string(buf, buf_length, out_str, &out_length, &is_last_chunk)) {
		uint8_t *new_out = (uint8_t*)realloc(out_str, out_length);
		if (NULL != new_out) {
			out_str = new_out;
		}
		HessianExternalOneByteStringResource resource(out_str, out_length);
		string = v8::String::NewExternalOneByte(isolate, &resource).ToLocalChecked();
		scope.Escape(string);
		args.GetReturnValue().Set(string);
		return 1;
	} else {
		free(out_str);
		return 0;
	}
}
