//
// Created by 王晓辰 on 15/10/2.
//

#include "test_listdir.h"

#include <libpath.h>
#include "tester.h"

#include <set>

bool test_listdir_check()
{
    std::string dirpath = "../test/testlistdir";

    std::set<std::string> right_set = {"dir1", "dir2", "file1", "file2"};

    for (auto node : ftxpath::listdir(dirpath))
    {
        if (right_set.find(node) == right_set.end())
        {
            return false;
        }
    }

    return true;
}

bool test_listdir() {

    LOG_TEST_STRING("");

    TEST_BOOL_TO_BOOL(test_listdir_check(), "test list dir failed");

    return true;
}
