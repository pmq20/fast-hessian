/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of v8-hessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#include "hessian.h"

void hessian_encode(const FunctionCallbackInfo<Value>& args) {
	Environment* env = Environment::GetCurrent(args);
	Local<Object> vbuf;
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
		Local<String> string = args[0].As<String>();

	} else {
		// TODO throw error
		return;
	}
	if (!ret) {
		// TODO throw error
		return;
	}
	vbuf = Buffer::New(env, data, length).ToLocalChecked();
	return args.GetReturnValue().Set(vbuf);
}

void hessian_decode(const FunctionCallbackInfo<Value>& args) {
}
