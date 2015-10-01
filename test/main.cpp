//
// Created by 王晓辰 on 15/10/1.
//

#include <cstdlib>
#include <string.h>

#include "test_cwd.h"


int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        return 1;
    }

    if (strcmp(argv[1], "cwd") == 0 && !test_cwd())
        return 1;

    return 0;
}