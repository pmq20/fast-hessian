/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of fast-hessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#ifndef HESSIAN_ENCODE_H_6392FA14
#define HESSIAN_ENCODE_H_6392FA14

#include "node.h"

v8::Local<v8::Uint8Array> hessian_encode_null(v8::Isolate *isolate);
v8::Local<v8::Uint8Array> hessian_encode_int(const int32_t val, v8::Isolate *isolate);
v8::Local<v8::Uint8Array> hessian_encode_date(const uint64_t milliEpoch, v8::Isolate *isolate);
v8::Local<v8::Uint8Array> hessian_encode_long(const int64_t val, v8::Isolate *isolate);
v8::Local<v8::Uint8Array> hessian_encode_string(const v8::Local<v8::String> &str, v8::Isolate *isolate);

#endif /* end of include guard: HESSIAN_ENCODE_H_6392FA14 */
