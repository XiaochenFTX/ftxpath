//
// Created by 王晓辰 on 15/10/2.
//

#include "test_abspath.h"

#include <ftxpath.h>
#include "tester.h"

bool test_abspath_absolute()
{
    std::string abspath = "/a/b/c";

#ifdef WIN32
	abspath = "c:\\a\\b\\c";
#endif

    return abspath == ftx::path::abspath(abspath);
}

bool test_abspath_relative()
{
    std::string relpath = "a/b/c";

#ifdef WIN32
	relpath = "a\\b\\c";
#endif

	std::string curpath = ftx::path::cwd();
	std::string abspath = ftx::path::join(curpath, relpath);

	return abspath == ftx::path::abspath(relpath);
}

bool test_abspath() {

    LOG_TEST_STRING("");

    TEST_BOOL_TO_BOOL(test_abspath_absolute(), "test absolute path error");

    TEST_BOOL_TO_BOOL(test_abspath_relative(), "test relative path error");

    return true;
}
