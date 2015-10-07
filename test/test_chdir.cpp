//
// Created by 王晓辰 on 15/10/7.
//

#include "test_chdir.h"

#include <libpath.h>
#include "tester.h"

bool test_chdir_relpath()
{
    std::string path = "../test/testlistdir";
    ftxpath::cd(path);

    return ftxpath::exists("dir1");
}

bool test_chdir_abspath()
{
    std::string path = "../test/testlistdir";
    std::string abspath = ftxpath::join(ftxpath::cwd(), path);
    ftxpath::cd(abspath);

    return ftxpath::exists("dir1");
}

bool test_chdir_notdir()
{
    std::string path = "../test/testlistdir/file1";

    return ftxpath::cd(path) != 0;
}

bool test_chdir() {
    LOG_TEST_STRING("");

    std::string cwd = ftxpath::cwd();

    TEST_BOOL_TO_BOOL(test_chdir_relpath(), "test chdir by relpath error");
    chdir(cwd.c_str());

    TEST_BOOL_TO_BOOL(test_chdir_abspath(), "test chdir by abspath error");
    chdir(cwd.c_str());

    TEST_BOOL_TO_BOOL(test_chdir_notdir(), "test chdir not dir error");
    chdir(cwd.c_str());
    return true;
}
