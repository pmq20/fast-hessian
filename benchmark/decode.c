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

uint32_t out32;
uint64_t out_date;
uint64_t out64;
char out_str[1024];
size_t out_length;

static void f1()
{
	hessian_decode_int(buffer, &out32);
}

static void f2()
{
	hessian_decode_date(buffer, &out_date);
}

static void f3()
{
	hessian_decode_long(buffer, &out64);
}

static void f4()
{
	hessian_decode_string(buffer, out_str, &out_length);
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

	hessian_encode_long(300, buffer);
	ops_sec("hessian2 decode: long", f3);

	hessian_encode_string("xxx1231231231231xxx123", 22, buffer);
	ops_sec("hessian2 decode: string", f4);

	return 0;
}
