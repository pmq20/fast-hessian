/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of libhessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#include "hessian.h"
#include "test.h"

static uint8_t buffer_out[1024];
static size_t buffer_length;

void test_string()
{
	char out_str[1024];
	size_t out_length;
	
	buffer_length = hessian_encode_string("xxx1231231231231xxx123", 22, buffer_out);
	EXPECT(hessian_decode_string(buffer_out, out_str, &out_length));
	EXPECT(0 == memcmp(out_str, "xxx1231231231231xxx123", 22));
	EXPECT(22 == out_length);
	
	fprintf(stderr, "\n");
	fflush(stderr);
}
