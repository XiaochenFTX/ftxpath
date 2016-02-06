//
// Created by 王晓辰 on 16/2/6.
//

#include "test_splitdrive.h"

#include <ftxpath.h>
#include "tester.h"


bool test_splitdrive_normal()
{
	std::string path = "c:/a/b";
	std::string head = "c:";
	std::string tail = "a/b";

	auto tuple = ftx::path::splitdrive(path);

	std::cout << std::get<0>(tuple) << "\n" << std::get<1>(tuple) << std::endl;

#ifdef WIN32
	return head == std::get<0>(tuple) && tail == std::get<1>(tuple);
#else
	return "" == std::get<0>(tuple) && path == std::get<1>(tuple);
#endif
}

bool test_splitdrive_unc()
{
	std::string path = "//machine/share/a/b/c";
	std::string head = "//machine/share";
	std::string tail = "a/b/c";

	auto tuple = ftx::path::splitdrive(path);

#ifdef WIN32
	return head == std::get<0>(tuple) && tail == std::get<1>(tuple);
#else
	return "" == std::get<0>(tuple) && path == std::get<1>(tuple);
#endif
}

bool test_splitdrive_root()
{
	std::string path = "/";

	auto tuple = ftx::path::splitdrive(path);

	return "" == std::get<0>(tuple) && path == std::get<1>(tuple);
}

bool test_splitdrive_slash()
{
	std::string path = "\\\\\\";

	auto tuple = ftx::path::splitdrive(path);

	return "" == std::get<0>(tuple) && path == std::get<1>(tuple);
}

bool test_splitdrive() {

    LOG_TEST_STRING("");

    TEST_BOOL_TO_BOOL(test_splitdrive_normal(), "test splitdrive normal case failed");

	TEST_BOOL_TO_BOOL(test_splitdrive_unc(), "test splitdrive unc format case failed");

	TEST_BOOL_TO_BOOL(test_splitdrive_root(), "test splitdrive root case failed");

	TEST_BOOL_TO_BOOL(test_splitdrive_slash(), "test splitdrive slash case failed");

    return true;
}
