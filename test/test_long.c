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

void test_long()
{
	uint64_t out;
	
	buffer_length = hessian_encode_long(12345678901234567890, buffer_out);
	EXPECT(hessian_decode_long(buffer_out, &out));
	EXPECT(12345678901234567890 == out);
	
	fprintf(stderr, "\n");
	fflush(stderr);
}
