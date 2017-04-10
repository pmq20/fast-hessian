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

void test_int()
{
	// it should read compact integers
	EXPECT(0 == hessian_decode_int(buffer1));
	EXPECT(-16 == hessian_decode_int(buffer2));
	EXPECT(47 == hessian_decode_int(buffer3));

	EXPECT(0 == hessian_decode_int(buffer4));
	EXPECT(-2048 == hessian_decode_int(buffer5));
	EXPECT(-256 == hessian_decode_int(buffer6));
	EXPECT(2047 == hessian_decode_int(buffer7));

	EXPECT(0 == hessian_decode_int(buffer8));
	EXPECT(-262144 == hessian_decode_int(buffer9));
	EXPECT(262143 == hessian_decode_int(buffer10));

	EXPECT(0 == hessian_decode_int(buffer11));
	EXPECT(300 == hessian_decode_int(buffer12));
}
