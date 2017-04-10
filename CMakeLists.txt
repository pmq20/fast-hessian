# Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
# 
# This file is part of libhessian, distributed under the MIT License
# For full terms see the included LICENSE file

PROJECT(libhessian C)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

OPTION(BUILD_TEST "Build a test of libhessian" OFF)

INCLUDE_DIRECTORIES(src include)
FILE(GLOB SRC_H include/hessian.h)
FILE(GLOB SRC src/*.c)
ADD_LIBRARY(hessian ${SRC_H} ${SRC})

IF(BUILD_TEST)
  ENABLE_TESTING()
  ADD_TEST(hessian_test hessian_test)
  FILE(GLOB SRC_TEST test/*.c)
  ADD_EXECUTABLE(hessian_test ${SRC_TEST})
  TARGET_LINK_LIBRARIES(hessian_test hessian)
ENDIF()
