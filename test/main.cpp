//
// Created by 王晓辰 on 15/10/1.
//

#include "tester.h"

#include "test_cwd.h"
#include "test_isabs.h"
#include "test_join.h"
#include "test_basename.h"


int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        return 1;
    }

    CASE_ONE_TEST_BY_ARGV1("cwd", test_cwd());
    CASE_ONE_TEST_BY_ARGV1("isabs", test_isabs());
    CASE_ONE_TEST_BY_ARGV1("join", test_join());
    CASE_ONE_TEST_BY_ARGV1("basename", test_basename());

    return 0;
}