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
	uint32_t x;
	hessian_decode_int(buffer, &x);
}

static void f2()
{
	uint64_t date;
	hessian_decode_date(buffer, &date);
}

int main(int argc, char const *argv[])
{
	struct timeval t;
	gettimeofday(&t, NULL);
	printf("== Libhessian Decode Benchmark ==\n");

	hessian_encode_int(1, buffer);
	ops_sec("hessian2 decode: number", f1);
	hessian_encode_date(t.tv_sec * 1e6 + t.tv_usec, buffer);
	ops_sec("hessian2 decode: date", f2);

	return 0;
}
