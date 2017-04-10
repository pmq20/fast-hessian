/*
 * Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
 *
 * This file is part of libhessian, distributed under the MIT License
 * For full terms see the included LICENSE file
 */

#ifndef TEST_H_30C20C35
#define TEST_H_30C20C35

#define EXPECT(cond) expect((cond), #cond, __FILE__, __LINE__)

void expect(short condition, const char *reason, const char* file, int line);
short fixture_eq(const char *name, uint8_t *out, size_t length);

#endif /* end of include guard: TEST_H_30C20C35 */
