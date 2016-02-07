//
// Created by 王晓辰 on 15/10/1.
//

#ifndef ftxpath_TESTER_H
#define ftxpath_TESTER_H

#include <string>
#include <iostream>
#include <cstdlib>

#ifdef WIN32
#include <direct.h>
#endif

#define TEST_BOOL_TO_BOOL(b, str)   \
if (!b)                              \
{                                   \
    std::cout<< str <<std::endl;    \
    return false;                   \
}

#define LOG_TEST_STRING(str)        \
std::cout   << __FUNCTION__         \
            << "  ************  "   \
            << str                  \
            << std::endl;

#define CASE_ONE_TEST_BY_ARGV1(pstr, b) \
if (strcmp(argv[1], pstr) == 0 && !b)   \
{                                       \
    return 1;                           \
}

#ifdef WIN32
#define S_ISDIR(st_mode) (_S_IFDIR & st_mode)
#define S_ISREG(st_mode) (_S_IFREG & st_mode)
#endif

#endif //ftxpath_TESTER_H
