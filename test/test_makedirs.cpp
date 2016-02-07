//
// Created by 王晓辰 on 15/10/7.
//

#include "test_makedirs.h"

#include <ftxpath.h>
#include "tester.h"

bool test_makedirs_one()
{
    std::string path = "../test/testmakedirs";
    ftx::path::makedirs(path);

	bool result = ftx::path::isdir(path);

    rmdir(path.c_str());

    return result;
}

bool test_makedirs_multi()
{
    std::string path = "../test/testmakedirs/dir1/dir2";
    std::string dir1 = "../test/testmakedirs";
    std::string dir2 = "../test/testmakedirs/dir1";
    std::string dir3 = "../test/testmakedirs/dir1/dir2";

	ftx::path::makedirs(path);

	bool res1 = ftx::path::isdir(dir1);
	bool res2 = ftx::path::isdir(dir2);
	bool res3 = ftx::path::isdir(dir3);

    if (res3)
    {
        rmdir(dir3.c_str());
    }
    if (res2)
    {
        rmdir(dir2.c_str());
    }
    if (res1)
    {
        rmdir(dir1.c_str());
    }

    return (res1 && res2 && res3);
}

bool test_makedirs() {
    LOG_TEST_STRING("");

    TEST_BOOL_TO_BOOL(test_makedirs_one(), "test makedirs one dir failed");

    TEST_BOOL_TO_BOOL(test_makedirs_multi(), "test makedirs multi dir failed");

    return true;
}
