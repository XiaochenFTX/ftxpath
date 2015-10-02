//
// Created by 王晓辰 on 15/10/2.
//

#include "test_basename.h"

#include <libpath.h>
#include "tester.h"

bool test_basename_dir()
{
    std::string path = "dir1/dir2/dir3";
    std::string basename = "dir3";

    return basename == ftxpath::basename(path);
}

bool test_basename_file()
{
    std::string filepath = "a.txt";
    std::string basename = "a.txt";

    return basename == ftxpath::basename(filepath);
}

bool test_basename_folder()
{
    std::string folderpath = "dir1/dir2/folder/";
    std::string folderbasename = "";

    return folderbasename == ftxpath::basename(folderpath);
}

bool test_basename() {

    LOG_TEST_STRING("")

    TEST_BOOL_TO_BOOL(test_basename_dir(), "dir basename failed");

    TEST_BOOL_TO_BOOL(test_basename_file(), "file path basename failed");

    TEST_BOOL_TO_BOOL(test_basename_folder(), "folder path basename failed");

    return true;
}