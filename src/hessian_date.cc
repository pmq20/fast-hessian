/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of fast-hessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#include "hessian.h"

short hessian_decode_date(uint8_t * const buf, const size_t buf_length, const v8::FunctionCallbackInfo<v8::Value>& args)
{
	node::Environment* env = node::Environment::GetCurrent(args);
	v8::EscapableHandleScope scope(env->isolate());
	uint8_t code = buf[0];
	if (buf_length >= 9 && code == 0x4a) {
		v8::Local<v8::Value> date = v8::Date::New(env->context(),
			ntohll(*(uint64_t *)(buf + 1))).ToLocalChecked();
		scope.Escape(date);
		args.GetReturnValue().Set(date);
		return 1;
	}
	if (buf_length >= 5 && code == 0x4b) {
		v8::Local<v8::Value> date = v8::Date::New(env->context(),
			*(uint32_t *)(buf + 1) * 60000).ToLocalChecked();
		scope.Escape(date);
		args.GetReturnValue().Set(date);
		return 1;
	}
	return 0;
}

v8::Local<v8::Uint8Array> hessian_encode_date(const uint64_t milliEpoch, v8::Isolate *isolate)
{
	v8::EscapableHandleScope handle_scope(isolate);
	if ((milliEpoch % 60000) == 0) {
		uint64_t minutes = milliEpoch / 60000;
		if (minutes <= 0x7fffffff) {
			v8::Local<v8::Uint8Array> ret = HessianPool::Get(isolate, 5);
			uint8_t* out = static_cast<uint8_t*>(ret->Buffer()->GetContents().Data()) + ret->ByteOffset();
			out[0] = 0x4b;
			*(int32_t *)(out + 1) = htonl((uint32_t)minutes);
			return handle_scope.Escape(ret);
		}
	}
	v8::Local<v8::Uint8Array> ret = HessianPool::Get(isolate, 9);
	uint8_t* out = static_cast<uint8_t*>(ret->Buffer()->GetContents().Data()) + ret->ByteOffset();
	out[0] = 0x4a;
	*(int64_t *)(out + 1) = htonll(milliEpoch);
	return handle_scope.Escape(ret);
}
