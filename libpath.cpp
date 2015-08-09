//
//  libpath.cpp
//  libpath
//
//  Created by 王晓辰 on 15/8/8.
//  Copyright (c) 2015年 ftxtool. All rights reserved.
//

#include "libpath.h"

#include "split.h"

#include <string>
#include <unistd.h>
#include <cstdlib>


const std::string curdir = ".";
const std::string pardir = "..";
const std::string extsep = ".";
const std::string sep = "/";
const std::string pathsep = ":";
const std::string defpath = ":/bin:/usr/bin";



std::string ftxpath::cwd()
{
    char* buff = getcwd(nullptr, 0);
    std::string path(buff);
    free(buff);
    
    return path;
}

bool ftxpath::isabs(const std::string &path)
{
    return path[0]=='/';
}

void _join(std::string& lpath, const std::string& rpth)
{
    if (rpth[0] == '/')
    {
        lpath = rpth;
    }
    else if (lpath.empty() || *(lpath.rbegin()) == '/')
    {
        lpath += rpth;
    }
    else
    {
        lpath += "/" + rpth;
    }

}

std::string ftxpath::join(const std::string &lpath, const std::string &rpath)
{
    std::string path = lpath;
    _join(path, rpath);
    return path;
}

std::string ftxpath::join(const std::string &lpath, const std::vector<std::string> &rpaths)
{
    std::string path = lpath;
    
    for (auto rp: rpaths)
    {
        _join(path, rp);
    }
    
    return path;
}

std::string ftxpath::basename(const std::string &path)
{
    auto pos = path.find_last_of('/');    
    return path.substr(pos + 1);
}

std::string ftxpath::dirname(const std::string &path)
{
    auto pos = path.find_last_of('/');
    return path.substr(0, pos);
}

std::tuple<std::string, std::string> ftxpath::split(const std::string &path)
{
    auto pos = path.find_last_of('/');
    return std::tuple<std::string, std::string>(path.substr(0, pos), path.substr(pos + 1));
}