//
// Created by 王晓辰 on 15/10/1.
//

#include "test_cwd.h"

#include <libpath.h>

#include "tester.h"

bool test_cwd() {
    std::string str_cwd = ftxpath::cwd();

    LOG_TEST_STRING(str_cwd);

    TEST_BOOL_TO_BOOL(str_cwd.empty(), "cwd empty");

    return true;
}
