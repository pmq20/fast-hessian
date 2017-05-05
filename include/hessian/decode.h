/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of fast-hessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#ifndef HESSIAN_DECODE_H_9A447E20
#define HESSIAN_DECODE_H_9A447E20

#include "node.h"

short hessian_decode_string(uint8_t * const buf, const size_t buf_length, const v8::FunctionCallbackInfo<v8::Value>& args);
short hessian_decode_bytes(uint8_t * const buf, const size_t buf_length, const v8::FunctionCallbackInfo<v8::Value>& args);
short hessian_decode_long(uint8_t * const buf, const size_t buf_length, const v8::FunctionCallbackInfo<v8::Value>& args);
short hessian_decode_object(uint8_t * const buf, const size_t buf_length, const v8::FunctionCallbackInfo<v8::Value>& args);
short hessian_decode_double(uint8_t * const buf, const size_t buf_length, const v8::FunctionCallbackInfo<v8::Value>& args);
short hessian_decode_bool(uint8_t * const buf, const size_t buf_length, const v8::FunctionCallbackInfo<v8::Value>& args);
short hessian_decode_hash_map(uint8_t * const buf, const size_t buf_length, const v8::FunctionCallbackInfo<v8::Value>& args);
short hessian_decode_int(uint8_t * const buf, const size_t buf_length, const v8::FunctionCallbackInfo<v8::Value>& args);
short hessian_decode_date(uint8_t * const buf, const size_t buf_length, const v8::FunctionCallbackInfo<v8::Value>& args);
short hessian_decode_map(uint8_t * const buf, const size_t buf_length, const v8::FunctionCallbackInfo<v8::Value>& args);
short hessian_decode_null(uint8_t * const buf, const size_t buf_length, const v8::FunctionCallbackInfo<v8::Value>& args);
short hessian_decode_ref(uint8_t * const buf, const size_t buf_length, const v8::FunctionCallbackInfo<v8::Value>& args);
short hessian_decode_array(uint8_t * const buf, const size_t buf_length, const v8::FunctionCallbackInfo<v8::Value>& args);

#endif /* end of include guard: HESSIAN_DECODE_H_9A447E20 */
