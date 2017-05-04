/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of fast-hessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#ifndef HESSIAN_H_B37B4F17
#define HESSIAN_H_B37B4F17

#ifdef _WIN32
#include <Winsock2.h>
#else
#include <arpa/inet.h>
#endif

#ifdef __linux__
#include <byteswap.h>
#define htonll __bswap_64
#define ntohll __bswap_64
#endif

#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include <stdint.h>
#include <stddef.h>

#include "hessian/encode.h"
#include "hessian/decode.h"

#include "node.h"

void hessian_encode(const v8::FunctionCallbackInfo<v8::Value>& args);
void hessian_decode(const v8::FunctionCallbackInfo<v8::Value>& args);

#endif /* end of include guard: HESSIAN_H_B37B4F17 */
