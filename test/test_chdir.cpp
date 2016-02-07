//
// Created by 王晓辰 on 15/10/7.
//

#include "test_chdir.h"

#include <ftxpath.h>
#include "tester.h"

bool test_chdir_relpath()
{
    std::string path = "../test/testlistdir";
    ftx::path::cd(path);

	return ftx::path::exists("dir1");
}

bool test_chdir_abspath()
{
    std::string path = "../test/testlistdir";
	std::string abspath = ftx::path::join(ftx::path::cwd(), path);
	ftx::path::cd(abspath);

	return ftx::path::exists("dir1");
}

bool test_chdir_notdir()
{
    std::string path = "../test/testlistdir/file1";

	return ftx::path::cd(path) != 0;
}

bool test_chdir() {
    LOG_TEST_STRING("");

	std::string cwd = ftx::path::cwd();

    TEST_BOOL_TO_BOOL(test_chdir_relpath(), "test chdir by relpath error");
    chdir(cwd.c_str());

    TEST_BOOL_TO_BOOL(test_chdir_abspath(), "test chdir by abspath error");
    chdir(cwd.c_str());

    TEST_BOOL_TO_BOOL(test_chdir_notdir(), "test chdir not dir error");
    chdir(cwd.c_str());
    return true;
}
