# Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
# 
# This file is part of libhessian, distributed under the MIT License
# For full terms see the included LICENSE file

PROJECT(libhessian C)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

OPTION(BUILD_BENCHMARK	"Build the benchmark of libhessian"	OFF)

INCLUDE_DIRECTORIES(src include)
FILE(GLOB SRC_H include/hessian.h include/hessian/*.h)
FILE(GLOB SRC src/*.c)
ADD_LIBRARY(hessian ${SRC_H} ${SRC})

IF(BUILD_BENCHMARK)
        ADD_EXECUTABLE(decode_benchmark benchmark/benchmark.h benchmark/benchmark.c benchmark/decode.c)
        TARGET_LINK_LIBRARIES(decode_benchmark hessian)

        ADD_EXECUTABLE(encode_benchmark benchmark/benchmark.h benchmark/benchmark.c benchmark/encode.c)
        TARGET_LINK_LIBRARIES(encode_benchmark hessian)
ENDIF()
