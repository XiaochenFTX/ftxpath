//
//  Generator.cpp
//  libpath
//
//  Created by 王晓辰 on 15/8/16.
//  Copyright (c) 2015年 ftxtool. All rights reserved.
//

#include "Generator.h"

#include "libpath.h"


PathGenerator::PathIterator::PathIterator(PathGenerator* generator)
: _generator(generator)
, _current()
{
    next();
}

PathGenerator::PathIterator& PathGenerator::PathIterator::operator++()
{
    _generator->popRoot();
    next();
    
    return *this;
}

bool PathGenerator::PathIterator::operator!=(const PathIterator& it)
{
    return !_generator->empty();
}

const PathGenerator::PathTuple& PathGenerator::PathIterator::operator*()
{
    return _current;
}

const PathGenerator::PathTuple& PathGenerator::PathIterator::next()
{
    std::string root = _generator->nextRoot();
    std::vector<std::string> folder_list;
    std::vector<std::string> file_list;
    
    for (auto name : ftxpath::listdir(root))
    {
        std::string full_name = ftxpath::join(root, name);
        if (ftxpath::isdir(full_name))
        {
            folder_list.push_back(name);
            _generator->pushFolder(full_name);
        }
        else
        {
            file_list.push_back(name);
        }
    }

    _current = std::make_tuple(root, folder_list, file_list);

    return _current;
}

PathGenerator::PathGenerator(const std::string& path)
: _roots({ftxpath::normpath(ftxpath::abspath(path))})
, _current(this)
{
}

const PathGenerator::PathIterator& PathGenerator::begin()
{
    return _current;
}

const PathGenerator::PathIterator& PathGenerator::end()
{
    return _current;
}

void PathGenerator::pushFolder(const std::string& folder)
{
    _roots.push_back(ftxpath::normpath(folder));
}

void PathGenerator::popRoot()
{
    if (_roots.empty())
    {
        return;
    }
    
    _roots.pop_front();
}

std::string PathGenerator::nextRoot()
{
    if (_roots.empty())
    {
        return std::string();
    }
    
    std::string root = _roots.back();
    if (!ftxpath::isdir(root))
    {
        return std::string();
    }
    
    return root;
}

bool PathGenerator::empty()
{
    return _roots.empty();
}