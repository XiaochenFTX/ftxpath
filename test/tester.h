//
// Created by 王晓辰 on 15/10/1.
//

#ifndef ftxpath_TESTER_H
#define ftxpath_TESTER_H

#include <string>
#include <iostream>
#include <cstdlib>

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


#endif //ftxpath_TESTER_H
