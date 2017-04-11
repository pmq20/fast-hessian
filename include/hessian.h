/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of libhessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#ifndef HESSIAN_H_B37B4F17
#define HESSIAN_H_B37B4F17

#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <arpa/inet.h>
#include <time.h>

#include "hessian/encode.h"
#include "hessian/decode.h"

#ifdef __linux__
#include <byteswap.h>
#define htonll __bswap_64
#define ntohll __bswap_64
#endif

#endif /* end of include guard: HESSIAN_H_B37B4F17 */
