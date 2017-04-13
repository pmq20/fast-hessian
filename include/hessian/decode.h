/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of libhessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#ifndef DECODE_H_9A447E20
#define DECODE_H_9A447E20

short hessian_decode_int(uint8_t *buffer, int32_t *out);
short hessian_decode_date(uint8_t *buffer, uint64_t *out);
short hessian_decode_long(uint8_t *buffer, uint64_t *out);
short hessian_decode_string(uint8_t *buffer, char *out_str, size_t *out_length);

#endif /* end of include guard: DECODE_H_9A447E20 */
