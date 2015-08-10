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

std::string _join(const std::string& str, const std::vector<std::string>& arr)
{
    if (arr.empty())
    {
        return "";
    }
    
    std::string result;
    for (auto iter = arr.cbegin();;)
    {
        result += *iter;
        if (++iter != arr.cend())
        {
            result += str;
        }
        else
        {
            break;
        }
    }
    
    return result;
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

std::string ftxpath::normpath(const std::string &path)
{
    if (path.empty())
    {
        return curdir;
    }
    
    int initial_slashes = 0;
    if (path[0] == '/')
    {
        initial_slashes = 1;
    }
    
    if (initial_slashes == 1 && path[1] == '/' && path[2] != '/')
    {
        initial_slashes = 2;
    }
    
    std::vector<std::string> comps;
    _split(path, '/', comps);
    
    std::vector<std::string> new_comps;
    for (auto comp : comps)
    {
        if (comp.empty() || comp == curdir)
        {
            continue;
        }
        
        if (comp != pardir || (initial_slashes == 0 && new_comps.empty()) || (!new_comps.empty() && *(new_comps.crbegin()) == pardir))
        {
            new_comps.push_back(comp);
        }
        else if (!new_comps.empty())
        {
            new_comps.pop_back();
        }
    }
    
    std::string slash = "/";
    std::string norm_path;
    if (initial_slashes != 0)
    {
        for (int i = 0; i < initial_slashes; ++i)
        {
            norm_path += slash;
        }
    }
    
    norm_path += _join(slash, new_comps);
    return norm_path;
}

std::string ftxpath::abspath(const std::string &path)
{
    std::string abs_path = path;
    if (!isabs(abs_path))
    {
        abs_path = join(cwd(), path);
    }
    return normpath(abs_path);
}
