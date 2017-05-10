/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of fast-hessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#include "hessian.h"

short hessian_decode_null(uint8_t * const buf, const size_t buf_length, const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (1 == buf_length && 'N' == buf[0]) {
		return 1;
	} else {
		return 0;
	}
}

v8::Local<v8::Uint8Array> hessian_encode_null(v8::Isolate *isolate)
{
	v8::EscapableHandleScope handle_scope(isolate);
	v8::Local<v8::Uint8Array> ret = HessianPool::Get(isolate, 1);
	uint8_t* out = static_cast<uint8_t*>(ret->Buffer()->GetContents().Data()) + ret->ByteOffset();
	out[0] = 'N';
	return handle_scope.Escape(ret);
}
