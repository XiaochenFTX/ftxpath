//
// Created by 王晓辰 on 15/10/2.
//

#include "test_exists.h"

#include <libpath.h>
#include "tester.h"

bool test_exists_check()
{
    std::string path = "../test/testlistdir";
    return ftxpath::exists(path);
}

bool test_exists_check_not()
{
    std::string path = "asdffds";
    return !ftxpath::exists(path);
}

bool test_exists() {

    LOG_TEST_STRING("");

    TEST_BOOL_TO_BOOL(test_exists_check(), "exists check error, is exists");

    TEST_BOOL_TO_BOOL(test_exists_check_not(), "exists checknot error, is not exists");

    return true;
}
