cmake_minimum_required(VERSION 3.1)
project(libpath)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(src bin)

if (NOT IOS)
	enable_testing()
	add_subdirectory(test test_bin)
endif(NOT IOS)