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
#include <dirent.h>
#include <sys/stat.h>


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

std::string _join_str(const std::string& str, const std::vector<std::string>& arr)
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
    if (path == "/")
    {
        return path;
    }

    auto pos = path.find_last_of('/');

    if (pos == std::string::npos)
    {
        return std::string();
    }

    return path.substr(0, pos);
}

std::tuple<std::string, std::string> ftxpath::split(const std::string &path)
{
    if (path == "/")
    {
        return std::tuple<std::string, std::string>(path, "");
    }

    auto pos = path.find_last_of('/');

    if (pos == std::string::npos)
    {
        return std::tuple<std::string, std::string>("", path);
    }

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
    
    norm_path += _join_str(slash, new_comps);
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

std::string ftxpath::relpath(const std::string &path, const std::string &start)
{
    std::vector<std::string> path_list;
    _split(abspath(path), '/', path_list);
    
    std::vector<std::string> start_list;
    _split(abspath(start), '/', start_list);
    
    std::vector<std::string> rel_list;
    
    auto path_it = path_list.cbegin();
    auto start_it = start_list.cbegin();
    for (;path_it != path_list.cend() && start_it != start_list.cend(); ++path_it, ++start_it)
    {
        if (*path_it != *start_it)
        {
            break;
        }
    }

    for (; start_it != start_list.cend(); ++start_it)
    {
        rel_list.push_back(pardir);
    }
    
    for (; path_it != path_list.cend(); ++path_it)
    {
        rel_list.push_back(*path_it);
    }
    
    std::string rel_path;
    for (auto node : rel_list)
    {
        _join(rel_path, node);
    }
    
    return rel_path;
}

std::vector<std::string> ftxpath::listdir(const std::string &path)
{
    std::vector<std::string> list_dir;
    DIR* pDir = opendir(path.c_str());
    if (pDir != nullptr)
    {
        struct dirent *ent;
        while ((ent=readdir(pDir)) != nullptr)
        {
            std::string name = ent->d_name;
            if (name == curdir || name == pardir)
            {
                continue;
            }
            list_dir.push_back(ent->d_name);
        }
        closedir(pDir);
    }
    
    return list_dir;
}

bool ftxpath::isdir(const std::string &path)
{
    struct stat buf;
    return stat(path.c_str(), &buf) == 0 && S_ISDIR(buf.st_mode);
}

bool ftxpath::isfile(const std::string &path)
{
    struct stat buf;
    return stat(path.c_str(), &buf) == 0 && S_ISREG(buf.st_mode);
}

PathGenerator ftxpath::walk(const std::string &path)
{
    return PathGenerator(path);
}

void ftxpath::walk(const std::string &path, std::function<void(std::string root, std::vector<std::string> folders, std::vector<std::string> files)> func)
{
    for (auto p : walk(path))
    {
        func(std::get<0>(p), std::get<1>(p), std::get<2>(p));
    }
}

bool ftxpath::exists(const std::string &path)
{
    struct stat buf;
    return stat(path.c_str(), &buf) == 0;
}

void _make_path_list(std::string& path, std::vector<std::string>& path_list)
{
    std::string abspath = ftxpath::normpath(ftxpath::abspath(path));
    _split(abspath, '/', path_list);
}

std::vector<std::string> _make_path_list(std::string& path)
{
    std::vector<std::string> path_list;
    _make_path_list(path, path_list);
    return path_list;
}

std::string ftxpath::commonprefix(std::string &path1,  std::string &path2)
{
    if (path1.empty() || path2.empty())
    {
        return std::string();
    }

    std::vector<std::string> path1_list = _make_path_list(path1);
    std::vector<std::string> path2_list = _make_path_list(path2);

    std::string common_path;
    for (auto i = 0; i < path1_list.size() && i < path2_list.size(); ++i)
    {
        std::string node1 = path1_list[i];
        std::string node2 = path2_list[i];
        if (node1 == node2)
        {
            _join(common_path, node1);
        }
        else
        {
            break;
        }
    }

    if (!common_path.empty())
    {
        common_path = "/" + common_path;
    }

    return common_path;
}

std::string ftxpath::commonprefix(std::vector<std::string> path_list)
{
    if (path_list.empty())
    {
        return std::string();
    }

    for (std::string path : path_list)
    {
        if (path.empty())
        {
            return std::string();
        }
    }

    std::vector<std::vector<std::string>> path_list_table;
    size_t min_size = 999999; // ... short than 999999
    for (std::string path : path_list)
    {
        std::vector<std::string> list = _make_path_list(path);
        if (list.size() < min_size)
        {
            min_size = list.size();
        }
        path_list_table.push_back(list);
    }

    std::string common_path;
    for (auto i = 0; i < min_size; ++i)
    {
        std::string common_node;
        for (auto list : path_list_table)
        {
            std::string node = list[i];
            if (common_node.empty())
            {
                common_node = node;
                continue;
            }

            if (node != common_node)
            {
                goto ENDING;
            }
        }

        _join(common_path, common_node);
    }

ENDING:

    if (!common_path.empty())
    {
        common_path = "/" + common_path;
    }

    return common_path;
}