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
	
	buffer_length = hessian_encode_string("Pure C implementation of Hessian 2.0 Serialization Protocol", 59, buffer_out);
	EXPECT(hessian_decode_string(buffer_out, out_str, &out_length));
	EXPECT(0 == strncmp(out_str, "Pure C implementation of Hessian 2.0 Serialization Protocol", 1024));
	EXPECT(59 == out_length);
	
	fprintf(stderr, "\n");
	fflush(stderr);
}
