//
// Created by 王晓辰 on 15/10/1.
//

#include "test_isabs.h"

#include <ftxpath.h>
#include "tester.h"

bool test_isabs_check_abspath()
{
    std::string abspath = "/a/b/c";
    return ftxpath::isabs(abspath);
}

bool test_isabs_check_relpath()
{
    std::string relpath = "../a/b/c";
    return !ftxpath::isabs(relpath);
}

bool test_isabs() {

    LOG_TEST_STRING("");

    TEST_BOOL_TO_BOOL(test_isabs_check_abspath(), "is abspath but return false");

    TEST_BOOL_TO_BOOL(test_isabs_check_relpath(), "is relpath but reutrn true");

    return true;
}
