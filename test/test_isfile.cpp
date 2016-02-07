//
// Created by 王晓辰 on 15/10/2.
//

#include "test_isfile.h"

#include <ftxpath.h>
#include "tester.h"

bool test_isfile_file()
{
    std::string path = "../test/testlistdir/file1";
    return ftx::path::isfile(path);
}

bool test_isfile_dir()
{
    std::string path = "../test/testlistdir";
	return !ftx::path::isfile(path);
}

bool test_isfile_ghost()
{
    std::string path = "asdfgh";
	return !ftx::path::isfile(path);
}

bool test_isfile() {

    LOG_TEST_STRING("");

    TEST_BOOL_TO_BOOL(test_isfile_file(), "return is not file but it is");

    TEST_BOOL_TO_BOOL(test_isfile_dir(), "return is file but it is not");

    TEST_BOOL_TO_BOOL(test_isfile_ghost(), "test is file error");

    return true;
}
