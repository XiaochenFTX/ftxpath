//
// Created by 王晓辰 on 15/10/1.
//

#ifndef LIBPATH_TESTER_H
#define LIBPATH_TESTER_H

#include <string>
#include <iostream>
#include <cstdlib>

#define TEST_BOOL_TO_BOOL(b1, b2)   \
if (b1)                             \
{                                   \
    std::cout<< b2 <<std::endl;     \
    return false;                   \
}

#define LOG_TEST_STRING(str)        \
std::cout   << __FUNCTION__         \
            << "  ************  "   \
            << str                  \
            << std::endl;


#endif //LIBPATH_TESTER_H
