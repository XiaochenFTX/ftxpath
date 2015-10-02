//
// Created by 王晓辰 on 15/10/2.
//

#include "test_isdir.h"

#include <libpath.h>
#include "tester.h"

bool test_isdir_dir()
{
    std::string path = "../test/testlistdir";
    return ftxpath::isdir(path);
}

bool test_isdir_file()
{
    std::string path = "../test/testlistdir/file1";
    return !ftxpath::isdir(path);
}

bool test_isdir_ghost()
{
    std::string path = "asdfgh";
    return !ftxpath::isdir(path);
}

bool test_isdir() {

    LOG_TEST_STRING("")

    TEST_BOOL_TO_BOOL(test_isdir_dir(), "return is not dir but it is");

    TEST_BOOL_TO_BOOL(test_isdir_file(), "return is dir but it is not");

    TEST_BOOL_TO_BOOL(test_isdir_ghost(), "test is dir error");

    return true;
}
