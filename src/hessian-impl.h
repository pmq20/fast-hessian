/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of libhessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#ifndef LIBHESSIAN_H_B37B4F17
#define LIBHESSIAN_H_B37B4F17

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

#include <assert.h>

#endif /* end of include guard: LIBHESSIAN_H_B37B4F17 */
