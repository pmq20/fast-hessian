/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of libhessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#include "hessian.h"
#include "test.h"

int main(int argc, char const *argv[])
{
	test_int();
	test_date();
	test_long();
	test_string();

	return 0;
}
