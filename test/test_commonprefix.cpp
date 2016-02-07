//
// Created by 王晓辰 on 15/10/3.
//

#include "test_commonprefix.h"

#include <ftxpath.h>
#include "tester.h"

bool test_commonprefix_exists()
{
    std::string curpath = ftx::path::cwd();
	std::string path1 = ftx::path::join(curpath, "../test/testlistdir/dir1");
	std::string path2 = ftx::path::join(curpath, "../test/testlistdir/dir2");

	std::string common = ftx::path::join(curpath, "../test/testlistdir");

	return (ftx::path::normpath(common) == ftx::path::commonprefix(path1, path2));
}

bool test_commonprefix_not_exists()
{
	std::string curpath = ftx::path::cwd();

    std::string path1 = "";
	std::string path2 = ftx::path::join(curpath, "../test");
    std::string path3 = "../test/testlistdir";

	return ftx::path::commonprefix({ path1, path2, path3 }).empty();
}

bool test_commonprefix_multipath()
{
	std::string curpath = ftx::path::cwd();
	std::string path1 = ftx::path::join(curpath, "../test/testlistdir/dir1");
	std::string path2 = ftx::path::join(curpath, "../test/testlistdir/dir2");
    std::string path3 = "../test/testlistdir/file1";
    std::string path4 = "../test/testlistdir/file2";

	std::string common = ftx::path::join(curpath, "../test/testlistdir");

	return (ftx::path::normpath(common) == ftx::path::commonprefix({ path1, path2, path3, path4 }));
}

bool test_commonprefix() {

    LOG_TEST_STRING("");

    TEST_BOOL_TO_BOOL(test_commonprefix_exists(), "common path error");

    TEST_BOOL_TO_BOOL(test_commonprefix_not_exists(), "common path not exists error");

    TEST_BOOL_TO_BOOL(test_commonprefix_multipath(), "common path multi path error");

    return true;
}
