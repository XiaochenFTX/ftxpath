//
// Created by 王晓辰 on 15/10/2.
//

#include "test_normpath.h"

#include <ftxpath.h>
#include "tester.h"

bool test_normpath_normal()
{
    std::string path = "/a/b/c";

#ifdef WIN32
	path = "c:\\a\\b\\c";
#endif
	
    return path == ftxpath::normpath(path);
}

bool test_normpath_pardir()
{
	std::cout << "aaaaaaaa" << std::endl;
    std::string path = "../a/b/c/../..";
    std::string normpath = "../a";

#ifdef WIN32
	normpath = "..\\a";
#endif

	std::cout << ftxpath::normpath(path) << std::endl;

    return normpath == ftxpath::normpath(path);
}

bool test_normpath_curdir()
{
    std::string path = "./a/b";
    std::string normpath = "a/b";

#ifdef WIN32
	normpath = "a\\b";
#endif

	std::cout << ftxpath::normpath(path) << std::endl;

    return normpath == ftxpath::normpath(path);
}

bool test_normpath() {

    LOG_TEST_STRING("");

    TEST_BOOL_TO_BOOL(test_normpath_normal(), "normal path error");

    TEST_BOOL_TO_BOOL(test_normpath_pardir(), "pardir path normal path error");

    TEST_BOOL_TO_BOOL(test_normpath_curdir(), "curdir path normal path error");

    return true;
}
