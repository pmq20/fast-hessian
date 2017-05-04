/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of fast-hessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#ifndef HESSIAN_ENCODE_H_6392FA14
#define HESSIAN_ENCODE_H_6392FA14

#include "node.h"

short hessian_encode_null(uint8_t **out, size_t *len);
short hessian_encode_int(int32_t val, uint8_t **out, size_t *len);
short hessian_encode_date(uint64_t milliEpoch, uint8_t **out, size_t *len);
short hessian_encode_long(int64_t val, uint8_t **out, size_t *len);
short hessian_encode_string(v8::Local<v8::String> &str, uint8_t **out, size_t *len);

#endif /* end of include guard: HESSIAN_ENCODE_H_6392FA14 */
