//
// Created by 王晓辰 on 15/10/7.
//

#include "test_rmtree.h"

#include <ftxpath.h>
#include "tester.h"

void make_test_tree()
{
    std::string path = "../test/testrmtree";
    std::string tree_folder1 = "dir1/dir2/dir3";
    std::string tree_folder2 = "dir1/dir4/dir5";
    std::string tree_file1 = "file1";
    std::string tree_file2 = "dir1/dir2/file2";
    std::string tree_file3 = "dir1/dir2/file3";
    std::string tree_file4 = "dir1/dir2/file4";
    std::string tree_file5 = "dir1/dir2/dir3/file5";
    std::string tree_file6 = "file6";

    ftxpath::makedirs(ftxpath::join(path, tree_folder1));
    ftxpath::makedirs(ftxpath::join(path, tree_folder2));

    FILE* fp = fopen(ftxpath::join(path, tree_file1).c_str(), "w");
    fclose(fp);
    fp = fopen(ftxpath::join(path, tree_file2).c_str(), "w");
    fclose(fp);
    fp = fopen(ftxpath::join(path, tree_file3).c_str(), "w");
    fclose(fp);
    fp = fopen(ftxpath::join(path, tree_file4).c_str(), "w");
    fclose(fp);
    fp = fopen(ftxpath::join(path, tree_file5).c_str(), "w");
    fclose(fp);
    fp = fopen(ftxpath::join(path, tree_file6).c_str(), "w");
    fclose(fp);
}

bool test_rmtree_check_make_tree()
{
    std::string path = "../test/testrmtree";
    return ftxpath::isdir(path);
}

bool test_rmtree_one_file()
{
    std::string path = "../test/testrmtree/file6";
    ftxpath::rmtree(path);

    return !ftxpath::exists(path);
}

bool test_rmtree_normal()
{
    std::string path = "../test/testrmtree";

    ftxpath::rmtree(path);

    return !ftxpath::exists(path);
}

bool test_rmtree() {
    LOG_TEST_STRING("");

    make_test_tree();

    TEST_BOOL_TO_BOOL(test_rmtree_check_make_tree(), "make test tree failed");

    TEST_BOOL_TO_BOOL(test_rmtree_one_file(), "test rmtree one file error");

    TEST_BOOL_TO_BOOL(test_rmtree_normal(), "test rmtree normal error");

    return true;
}
