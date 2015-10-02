//
// Created by 王晓辰 on 15/10/2.
//

#include "test_normpath.h"

#include <libpath.h>
#include "tester.h"

bool test_normpath_normal()
{
    std::string path = "/a/b/c";
    return path == ftxpath::normpath(path);
}

bool test_normpath_pardir()
{
    std::string path = "../a/b/c/../..";
    std::string normpath = "../a";

    return normpath == ftxpath::normpath(path);
}

bool test_normpath_curdir()
{
    std::string path = "./a/b";
    std::string normpath = "a/b";

    return normpath == ftxpath::normpath(path);
}

bool test_normpath() {

    LOG_TEST_STRING("");

    TEST_BOOL_TO_BOOL(test_normpath_normal(), "normal path error");

    TEST_BOOL_TO_BOOL(test_normpath_pardir(), "pardir path normal path error");

    TEST_BOOL_TO_BOOL(test_normpath_curdir(), "curdir path normal path error");

    return true;
}
