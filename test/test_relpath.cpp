//
// Created by 王晓辰 on 15/10/2.
//

#include "test_relpath.h"

#include <ftxpath.h>
#include "tester.h"

bool test_relpath_relative()
{
    std::string relpath = "a/b/c";

    return relpath == ftxpath::relpath(relpath);
}

bool test_relpath_relative_start()
{
    std::string relpath = "a/b/c";
    std::string startpath = "a/b";
    std::string result = ftxpath::relpath(relpath, startpath);

    std::cout<< "test relpath start relative: " << result <<std::endl;

    std::string right_res = "c";

    return right_res == result;
}

bool test_relpath_absolute_start()
{
    std::string relpath = "a/b/c";
    std::string startpath = "/a/b";

#ifdef WIN32
	startpath = "c:\\a\\b";
#endif

    std::string result = ftxpath::relpath(relpath, startpath);

    std::cout<< "test relpath start absolute: " << result <<std::endl;

    std::string curpath = ftxpath::cwd();

    std::string right_res = "../.." + curpath + "/" + relpath;

    return right_res == result;
}

bool test_relpath() {

    LOG_TEST_STRING("");

    TEST_BOOL_TO_BOOL(test_relpath_relative(), "test relative path error");

    TEST_BOOL_TO_BOOL(test_relpath_relative_start(), "test relpath start relative path error");

    TEST_BOOL_TO_BOOL(test_relpath_absolute_start(), "test relpath start absolute path error");

    return true;
}
