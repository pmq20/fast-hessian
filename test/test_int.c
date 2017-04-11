/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of libhessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#include "hessian.h"
#include "test.h"

static uint8_t buffer1[] = { 0x90 };
static uint8_t buffer2[] = { 0x80 };
static uint8_t buffer3[] = { 0xbf };

static uint8_t buffer4[] = { 0xc8, 0x00 };
static uint8_t buffer5[] = { 0xc0, 0x00 };
static uint8_t buffer6[] = { 0xc7, 0x00 };
static uint8_t buffer7[] = { 0xcf, 0xff };

static uint8_t buffer8[] = { 0xd4, 0x00, 0x00 };
static uint8_t buffer9[] = { 0xd0, 0x00, 0x00 };
static uint8_t buffer10[] = { 0xd7, 0xff, 0xff };

static uint8_t buffer11[] = { (uint8_t)'I', 0x00, 0x00, 0x00, 0x00 };
static uint8_t buffer12[] = { (uint8_t)'I', 0x00, 0x00, 0x01, 0x2c };

static uint8_t buffer_out[1024];
static size_t buffer_length;

void test_int()
{
	int32_t out;
	
	// it should read compact integers
	EXPECT(hessian_decode_int(buffer1, &out));
	EXPECT(0 == out);
	EXPECT(hessian_decode_int(buffer2, &out));
	EXPECT(-16 == out);
	EXPECT(hessian_decode_int(buffer3, &out));
	EXPECT(47 == out);

	EXPECT(hessian_decode_int(buffer4, &out));
	EXPECT(0 == out);
	EXPECT(hessian_decode_int(buffer5, &out));
	EXPECT(-2048 == out);
	EXPECT(hessian_decode_int(buffer6, &out));
	EXPECT(-256 == out);
	EXPECT(hessian_decode_int(buffer7, &out));
	EXPECT(2047 == out);

	EXPECT(hessian_decode_int(buffer8, &out));
	EXPECT(0 == out);
	EXPECT(hessian_decode_int(buffer9, &out));
	EXPECT(-262144 == out);
	EXPECT(hessian_decode_int(buffer10, &out));
	EXPECT(262143 == out);

	EXPECT(hessian_decode_int(buffer11, &out));
	EXPECT(0 == out);
	EXPECT(hessian_decode_int(buffer12, &out));
	EXPECT(300 == out);

	// it should write number as java write
	buffer_length = hessian_encode_int(0, buffer_out);
	EXPECT(fixture_eq("number/0.bin", buffer_out, buffer_length));
	buffer_length = hessian_encode_int(1, buffer_out);
	EXPECT(fixture_eq("number/1.bin", buffer_out, buffer_length));
	buffer_length = hessian_encode_int(10, buffer_out);
	EXPECT(fixture_eq("number/10.bin", buffer_out, buffer_length));
	buffer_length = hessian_encode_int(16, buffer_out);
	EXPECT(fixture_eq("number/16.bin", buffer_out, buffer_length));
	buffer_length = hessian_encode_int(2047, buffer_out);
	EXPECT(fixture_eq("number/2047.bin", buffer_out, buffer_length));
	buffer_length = hessian_encode_int(255, buffer_out);
	EXPECT(fixture_eq("number/255.bin", buffer_out, buffer_length));
	buffer_length = hessian_encode_int(256, buffer_out);
	EXPECT(fixture_eq("number/256.bin", buffer_out, buffer_length));
	buffer_length = hessian_encode_int(262143, buffer_out);
	EXPECT(fixture_eq("number/262143.bin", buffer_out, buffer_length));
	buffer_length = hessian_encode_int(262144, buffer_out);
	EXPECT(fixture_eq("number/262144.bin", buffer_out, buffer_length));
	buffer_length = hessian_encode_int(46, buffer_out);
	EXPECT(fixture_eq("number/46.bin", buffer_out, buffer_length));
	buffer_length = hessian_encode_int(47, buffer_out);
	EXPECT(fixture_eq("number/47.bin", buffer_out, buffer_length));
	buffer_length = hessian_encode_int(-16, buffer_out);
	EXPECT(fixture_eq("number/-16.bin", buffer_out, buffer_length));
	buffer_length = hessian_encode_int(-2048, buffer_out);
	EXPECT(fixture_eq("number/-2048.bin", buffer_out, buffer_length));
	buffer_length = hessian_encode_int(-256, buffer_out);
	EXPECT(fixture_eq("number/-256.bin", buffer_out, buffer_length));
	buffer_length = hessian_encode_int(-262144, buffer_out);
	EXPECT(fixture_eq("number/-262144.bin", buffer_out, buffer_length));
	buffer_length = hessian_encode_int(-262145, buffer_out);
	EXPECT(fixture_eq("number/-262145.bin", buffer_out, buffer_length));
	
	fprintf(stderr, "\n");
	fflush(stderr);
}
