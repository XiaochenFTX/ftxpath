//
// Created by 王晓辰 on 15/10/1.
//

#include "tester.h"

#include "test_cwd.h"


int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        return 1;
    }

    CASE_ONE_TEST_BY_ARGV1("cwd", test_cwd());


    return 0;
}