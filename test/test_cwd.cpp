//
// Created by 王晓辰 on 15/10/1.
//

#include "test_cwd.h"

#include <libpath.h>

#include <string>
#include <iostream>

bool test_cwd() {
    std::string str_cwd = ftxpath::cwd();

    std::cout << "test_cwd ******* " << str_cwd <<std::endl;

    if(str_cwd.empty())
    {
        std::cout << "cwd empty" <<std::endl;
        return false;
    }

    return true;
}
