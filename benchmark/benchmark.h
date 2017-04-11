/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of libhessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#ifndef BENCHMARK_H_54E84DB0
#define BENCHMARK_H_54E84DB0

#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>

void ops_sec(const char* title, void (*action_func)());

#endif /* end of include guard: BENCHMARK_H_54E84DB0 */
