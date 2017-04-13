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

void test_date()
{
	uint64_t out;

	buffer_length = hessian_encode_date(123456789012345, buffer_out);
	EXPECT(hessian_decode_date(buffer_out, &out));
	EXPECT(123456789012345 == out);

	fprintf(stderr, "\n");
	fflush(stderr);
}
