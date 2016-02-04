//
// Created by 王晓辰 on 15/10/1.
//

#include "test_cwd.h"

#include <ftxpath.h>
#include "tester.h"

#include <sys/stat.h>
#include <direct.h>

std::string mycwd()
{
	char* buff = nullptr;
    
#ifdef WIN32
	buff = _getcwd(nullptr, 0);
#else
	buff = getcwd(nullptr, 0);
#endif

	std::string path(buff);
	
	if (buff != nullptr)
	{
		free(buff);
	}

    return path;
}

bool test_cwd_isdir(std::string path)
{
    struct stat buf;
    return stat(path.c_str(), &buf) == 0 && S_ISDIR(buf.st_mode);
}

bool test_cwd() {
    std::string str_cwd = ftxpath::cwd();

    LOG_TEST_STRING(str_cwd);

    TEST_BOOL_TO_BOOL(!str_cwd.empty(), "cwd empty");

    TEST_BOOL_TO_BOOL((mycwd() == str_cwd), "cwd path error");

    TEST_BOOL_TO_BOOL(test_cwd_isdir(str_cwd), "cwd not dir");


    return true;
}
