//
// Created by 王晓辰 on 15/10/2.
//

#include "test_dirname.h"

#include <ftxpath.h>
#include "tester.h"

bool test_dirname_path()
{
    std::string path = "/a/b/c/d";
    std::string dirname = "/a/b/c";

	return dirname == ftx::path::dirname(path);
}

bool test_dirname_onename()
{
    std::string name = "name";
	return ftx::path::dirname(name).empty();
}

bool test_dirname_filepath()
{
    std::string filepath = "a/b/c/d.txt";
    std::string dirname = "a/b/c";

	return dirname == ftx::path::dirname(filepath);
}

bool test_dirname_folderpath()
{
    std::string folderpath = "a/b/c/folder/";
    std::string dirname = "a/b/c/folder";

	return dirname == ftx::path::dirname(folderpath);
}

bool test_dirname_root()
{
    std::string root = "/";

	return root == ftx::path::dirname(root);
}

bool test_dirname() {

    LOG_TEST_STRING("");

    TEST_BOOL_TO_BOOL(test_dirname_path(), "dir dirname failed");

    TEST_BOOL_TO_BOOL(test_dirname_onename(), "one name dirname failed");

    TEST_BOOL_TO_BOOL(test_dirname_filepath(), "file path dirname failed");

    TEST_BOOL_TO_BOOL(test_dirname_folderpath(), "folder path dirname failed");

    TEST_BOOL_TO_BOOL(test_dirname_root(), "root dirname failed");

    return true;
}
