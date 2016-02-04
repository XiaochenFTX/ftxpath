//
// Created by 王晓辰 on 15/10/2.
//

#include "test_join.h"

#include <ftxpath.h>
#include "tester.h"

bool join_string()
{
    std::string result = ftxpath::join("dir1", "dir2");
    std::string right_res = "dir1/dir2";

    std::cout<< "join str & str result: " << result <<std::endl;

    return right_res == result;
}

bool join_vec()
{
    std::string result = ftxpath::join("dir", {"a", "b", "c", "d"});
    std::string right_res = "dir/a/b/c/d";

    std::cout<< "join str & vector result: " << result <<std::endl;

    return right_res == result;
}

bool join_path_str()
{
    std::string result = ftxpath::join("dir1/dir2/dir3", "a/b/c/d");
    std::string right_res = "dir1/dir2/dir3/a/b/c/d";

    std::cout<< "join path & str result: " << result <<std::endl;

    return right_res == result;
}

bool join_path_vec()
{
    std::string result = ftxpath::join("dir1/dir2/dir3", {"ab", "aa/bb", "abc", "c", "a/b/c"});
    std::string right_res = "dir1/dir2/dir3/ab/aa/bb/abc/c/a/b/c";

    std::cout<< "join path & path vector result: " << result <<std::endl;

    return right_res == result;
}

bool test_join() {

    LOG_TEST_STRING("");

    TEST_BOOL_TO_BOOL(join_string(), "join str & str failed");

    TEST_BOOL_TO_BOOL(join_vec(), "join str & vec failed");

    TEST_BOOL_TO_BOOL(join_path_str(), "join path & path str failed");

    TEST_BOOL_TO_BOOL(join_path_vec(), "join path & path vec failed");

    return true;
}
