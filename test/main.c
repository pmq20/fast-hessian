/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of libhessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#include "hessian.h"

extern const uint8_t libhessian_fixture[];

static void expect(short condition, const char *reason)
{
	if (condition) {
		fprintf(stderr, ".");
	}
	else {
		fprintf(stderr, "x");
		fprintf(stderr, "\nFAILED: %s\n", reason);
		exit(1);
	}
	fflush(stderr);
}

int main(int argc, char const *argv[])
{
	expect(1);
	
	return 0;
}
