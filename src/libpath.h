//
//  libpath.h
//  libpath
//
//  Created by 王晓辰 on 15/8/8.
//  Copyright (c) 2015年 ftxtool. All rights reserved.
//

#ifndef __libpath__libpath__
#define __libpath__libpath__

#include <string>
#include <vector>
#include <functional>
#include "Generator.h"

namespace ftxpath {
    
    std::string cwd();
    
    bool isabs(const std::string&);
    
    std::string join(const std::string&, const std::string&);
    std::string join(const std::string&, const std::vector<std::string>&);
    
    std::string basename(const std::string&);
    std::string dirname(const std::string&);
    
    std::tuple<std::string, std::string> split(const std::string&);
    
    std::string normpath(const std::string&);
    
    std::string abspath(const std::string&);
    std::string relpath(const std::string&, const std::string& start = "");
    
    std::vector<std::string> listdir(const std::string&);
    bool isdir(const std::string&);
    bool isfile(const std::string&);
    
    /*
    for (auto p : walk(path))
    {
        std::cout<< std::get<0>(p) <<std::endl;
        for (auto folder : std::get<1>(p))
        {
            std::cout<< folder <<std::endl;
        }
        for (auto file : std::get<2>(p))
        {
            std::cout<< file <<std::endl;
        }
    }
     */
    PathGenerator walk(const std::string&);
    
    /*
    walk(path, [](std::string root, std::vector<std::string> folders, std::vector<std::string> files){
        std::cout<< root <<std::endl;
        for (auto folder : folders)
        {
            std::cout<< folder <<std::endl;
        }
        for (auto file : files)
        {
            std::cout<< file <<std::endl;
        }
    });
     */
    void walk(const std::string&, std::function<void(std::string root, std::vector<std::string> folders, std::vector<std::string> files)>);
    
    bool exists(const std::string&);

    std::string commonprefix(std::string&, std::string&);
    std::string commonprefix(std::vector<std::string>&);
}

#endif /* defined(__libpath__libpath__) */
