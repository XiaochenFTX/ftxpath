//
// Created by 王晓辰 on 15/10/2.
//

#include "test_relpath.h"

#include <ftxpath.h>
#include "tester.h"

bool test_relpath_relative()
{
    std::string relpath = "a/b/c";

#ifdef WIN32
	relpath = "a\\b\\c";
#endif

    return relpath == ftx::path::relpath(relpath);
}

bool test_relpath_relative_start()
{
    std::string relpath = "a/b/c";
    std::string startpath = "a/b";
	std::string result = ftx::path::relpath(relpath, startpath);

    std::string right_res = "c";

    return right_res == result;
}

bool test_relpath_absolute_start()
{
    std::string relpath = "a/b/c";
    std::string startpath = "/a/b";

#ifdef WIN32
	startpath = "\\a\\b";
#endif

	std::string result = ftx::path::relpath(relpath, startpath);

	std::string curpath = ftx::path::cwd();

    std::string right_res = "../.." + curpath + "/" + relpath;

#ifdef WIN32
	std::tie(std::ignore, curpath) = ftx::path::splitdrive(curpath);
	right_res = "..\\.." + curpath + "\\" + relpath;
	right_res = ftx::path::normpath(right_res);
#endif

    return right_res == result;
}

bool test_relpath() {

    LOG_TEST_STRING("");

    TEST_BOOL_TO_BOOL(test_relpath_relative(), "test relative path error");

    TEST_BOOL_TO_BOOL(test_relpath_relative_start(), "test relpath start relative path error");

    TEST_BOOL_TO_BOOL(test_relpath_absolute_start(), "test relpath start absolute path error");

    return true;
}
