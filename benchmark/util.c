/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of libhessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#include "benchmark.h"

#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>

static void printfcomma (unsigned long long n) {
	if (n < 1000) {
		printf ("%llu", n);
		return;
	}
	printfcomma (n/1000);
	printf (",%03llu", n%1000);
}

void ops_sec(const char* title, void (*action_func)())
{
	unsigned long long sum = 0;
	struct timeval t;
	double before_sec, after_sec;
	size_t i;
	
	for(i = 0; i < 3; ++i)
	{
		gettimeofday(&t, NULL);
		before_sec = t.tv_sec + t.tv_usec * 1e-6;
		after_sec = before_sec + 1;
		
		while (t.tv_sec + t.tv_usec * 1e-6 < after_sec) {
			sum += 1;
			gettimeofday(&t, NULL);
			action_func();
		}
	}
	
	printf("%s x ", title);
	printfcomma(sum / 3);
	printf(" ops/sec\n");
}
