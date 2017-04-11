/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of libhessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#include "hessian.h"
#include "benchmark.h"
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

static uint8_t buffer[1024];

static void f1()
{
	hessian_encode_int(1, buffer);
}

static void f2()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	hessian_encode_date(t.tv_sec * 1e6 + t.tv_usec, buffer);
}
static void f3()
{
	hessian_encode_long(300, buffer);
}

int main(int argc, char const *argv[])
{
	printf("== Libhessian Encode Benchmark ==\n");

	ops_sec("hessian2 encode: number", f1);
	ops_sec("hessian2 encode: date", f2);
	ops_sec("hessian2 encode: long", f3);

	return 0;
}
