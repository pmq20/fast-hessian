/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of fast-hessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#ifndef HESSIAN_DECODE_H_9A447E20
#define HESSIAN_DECODE_H_9A447E20

#include "node.h"

short hessian_decode_null(uint8_t *buffer);
short hessian_decode_int(uint8_t *buffer, int32_t *out);
short hessian_decode_date(uint8_t *buffer, uint64_t *out);
short hessian_decode_long(uint8_t *buffer, int64_t *out);
short hessian_decode_string(uint8_t *buffer, char *out_str, size_t *out_length);

#endif /* end of include guard: HESSIAN_DECODE_H_9A447E20 */
