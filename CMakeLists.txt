cmake_minimum_required(VERSION 3.1)
project(libpath)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(src bin)

enable_testing()
add_subdirectory(test test_bin)