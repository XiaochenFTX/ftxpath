//
// Created by 王晓辰 on 15/10/2.
//

#include "test_walk.h"

#include <libpath.h>
#include "tester.h"

bool test_walk_ghost()
{
    std::string path = "asdfgh";

    for (auto p : ftxpath::walk(path))
    {
        if (!std::get<0>(p).empty())
        {
            std::cout<< "walk ghost root not empty" <<std::endl;
            return false;
        }

        if (!std::get<1>(p).empty())
        {
            std::cout<< "walk ghost dirs not empty" <<std::endl;
            return false;
        }

        if (!std::get<2>(p).empty())
        {
            std::cout<< "walk ghost files not empty" <<std::endl;
            return false;
        }
    }

    return true;
}

int state = 0;
bool test_walk_check()
{
    std::string path = "../test/testlistdir";

    for (auto p : ftxpath::walk(ftxpath::abspath(path)))
    {
        std::string root = std::get<0>(p);
        if (root.empty())
        {
            std::cout<< "walk check root empty" <<std::endl;
            return false;
        }
        if (!ftxpath::isdir(root))
        {
            std::cout<< "walk check root not dir" <<std::endl;
            return false;
        }

        auto dirs = std::get<1>(p);
        if (dirs.empty() && state == 0)
        {
            std::cout<< "walk check dirs empty" <<std::endl;
            return false;
        }
        for (auto dir : std::get<1>(p))
        {
            if (!ftxpath::isdir(ftxpath::join(root, dir)))
            {
                std::cout<< "walk check dir but not dir" <<std::endl;
                return false;
            }
        }

        auto files = std::get<2>(p);
        if (files.empty())
        {
            std::cout<< "walk check files empty" <<std::endl;
            return false;
        }
        for (auto file : std::get<2>(p))
        {
            if (!ftxpath::isfile(ftxpath::join(root, file)))
            {
                std::cout<< "walk check file but not file" <<std::endl;
                return false;
            }
        }

        state = 1;
    }

    return true;
}

bool test_walk() {

    LOG_TEST_STRING("")

    TEST_BOOL_TO_BOOL(test_walk_ghost(), "walk ghost error");

    TEST_BOOL_TO_BOOL(test_walk_check(), "walk check error");

    return true;
}
