/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of libhessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#include "hessian.h"
#include <stdio.h>

void expect(short condition, const char *reason, const char* file, int line)
{
	if (condition) {
		fprintf(stderr, ".");
	}
	else {
		fprintf(stderr, "x");
		fprintf(stderr, "\nFAILED: %s\n", reason);
		fprintf(stderr, "%s: %d\n", file, line);
		exit(1);
	}
	fflush(stderr);
}
