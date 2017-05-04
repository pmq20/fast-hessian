/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of fast-hessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#include "hessian.h"

#include "env.h"

void hessian_encode(const v8::FunctionCallbackInfo<v8::Value>& args) {
	node::Environment* env = node::Environment::GetCurrent(args);
	v8::Local<v8::Object> vbuf;
	char *data;
	size_t length;
	short ret;

	if (args[0]->IsNullOrUndefined()) {
		ret = hessian_encode_null((uint8_t**)(&data), &length);
	} else if (args[0]->IsNumber()) {
		int64_t x = args[0]->IntegerValue();
		if (x >= LONG_MAX || x < LONG_MIN) {
			ret = hessian_encode_long(x, (uint8_t**)(&data), &length);
		} else {
			ret = hessian_encode_int((int32_t)x, (uint8_t**)(&data), &length);
		}
	} else if (args[0]->IsDate()) {
		double x = args[0].As<v8::Date>()->ValueOf();
		ret = hessian_encode_date((uint64_t)x, (uint8_t**)(&data), &length);
	} else if (args[0]->IsString()) {
		v8::Local<v8::String> string = args[0].As<v8::String>();

	} else {
		// TODO throw error
		return;
	}
	if (!ret) {
		// TODO throw error
		return;
	}
	vbuf = node::Buffer::New(env, data, length).ToLocalChecked();
	return args.GetReturnValue().Set(vbuf);
}

void hessian_decode(const v8::FunctionCallbackInfo<v8::Value>& args) {
}
