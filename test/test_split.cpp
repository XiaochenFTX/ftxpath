//
// Created by 王晓辰 on 15/10/2.
//

#include "test_split.h"

#include <libpath.h>
#include "tester.h"

bool test_split_path()
{
    std::string path = "/a/b/c";
    std::string res1 = "/a/b";
    std::string res2 = "c";

    auto tuple = ftxpath::split(path);

    return res1 == std::get<0>(tuple) && res2 == std::get<1>(tuple);
}

bool test_split_onename()
{
    std::string name = "name";

    auto tuple = ftxpath::split(name);

    return std::get<0>(tuple).empty() && name == std::get<1>(tuple);
}

bool test_split_folderpath()
{
    std::string folderpath = "a/b/c/";
    std::string basename = "a/b/c";

    auto tuple = ftxpath::split(folderpath);

    return basename == std::get<0>(tuple) && std::get<1>(tuple).empty();
}

bool test_split_root()
{
    std::string root = "/";

    auto tuple = ftxpath::split(root);

    return root == std::get<0>(tuple) && std::get<1>(tuple).empty();
}

bool test_split() {

    LOG_TEST_STRING("")

    TEST_BOOL_TO_BOOL(test_split_path(), "split path failed");

    TEST_BOOL_TO_BOOL(test_split_onename(), "split one name failed");

    TEST_BOOL_TO_BOOL(test_split_folderpath(), "split folder path failed");

    TEST_BOOL_TO_BOOL(test_split_root(), "split root failed");

    return true;
}
