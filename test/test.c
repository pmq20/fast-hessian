/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of libhessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#include "hessian.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

short fixture_eq(const char *name, uint8_t *buf, size_t length)
{
	FILE *f = fopen(name, "r");
	int c, l = 0;
	assert(f);
	while (1) {
		c = getc(f);
		if (EOF == c) {
			fclose(f);
			return (l == length) ? 1 : 0;
		}
		++l;
		if (l > length) {
			fclose(f);
			return 0;
		}
		if ((uint8_t)c != buf[l - 1]) {
			fclose(f);
			return 0;
		}
	}
	assert(0);
	return -1;
}
