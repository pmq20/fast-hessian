/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of libhessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#include "hessian.h"
#include "benchmark.h"
#include <stdio.h>

static uint8_t buffer[1024];

static void f1()
{
	hessian_encode_int(1, buffer);
}

int main(int argc, char const *argv[])
{
	printf("== Libhessian Encode Benchmark ==\n");

	ops_sec("hessian2 encode: number", f1);

	return 0;
}
