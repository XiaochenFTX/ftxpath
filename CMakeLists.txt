cmake_minimum_required(VERSION 3.1)
project(libpath)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Generator.cpp
    Generator.h
    libpath.cpp
    libpath.h
    split.cpp
    split.h)

add_library(ftxpath STATIC ${SOURCE_FILES})