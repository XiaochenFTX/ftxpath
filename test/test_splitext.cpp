//
// Created by 王晓辰 on 15/10/3.
//

#include "test_splitext.h"

#include <ftxpath.h>
#include "tester.h"

bool test_splitext_normal()
{
    std::string path = "/a/b/c/a.txt";
    std::string root = "/a/b/c/a";
    std::string ext = ".txt";

    auto tuple = ftxpath::splitext(path);

    return root == std::get<0>(tuple) && ext == std::get<1>(tuple);
}

bool test_splitext_noext()
{
    std::string path = "a/s/d/f/";

    auto tuple = ftxpath::splitext(path);

    return path == std::get<0>(tuple) && std::get<1>(tuple).empty();
}

bool test_splitext_onefile()
{
    std::string path = "a.a.a";
    std::string root = "a.a";
    std::string ext = ".a";

    auto tuple = ftxpath::splitext(path);

    return root == std::get<0>(tuple) && ext == std::get<1>(tuple);
}

bool test_splitext_hidefile()
{
    std::string path = "a/b/.ext";

    auto tuple = ftxpath::splitext(path);

    return path == std::get<0>(tuple) && std::get<1>(tuple).empty();
}

bool test_splitext_multidot()
{
    std::string path = "a.a/b.b.b/c.c.c/../a.b.b.b";
    std::string root = "a.a/b.b.b/c.c.c/../a.b.b";
    std::string ext = ".b";

    auto tuple = ftxpath::splitext(path);

    return root == std::get<0>(tuple) && ext == std::get<1>(tuple);
}

bool test_splitext() {

    LOG_TEST_STRING("");

    TEST_BOOL_TO_BOOL(test_splitext_normal(), "test splitext normal case failed");

    TEST_BOOL_TO_BOOL(test_splitext_noext(), "test splitext no ext case failed");

    TEST_BOOL_TO_BOOL(test_splitext_onefile(), "test splitext one file case failed");

    TEST_BOOL_TO_BOOL(test_splitext_hidefile(), "test splitext hide file case failed");

    TEST_BOOL_TO_BOOL(test_splitext_multidot(), "test splitext multi dot case failed");

    return true;
}
