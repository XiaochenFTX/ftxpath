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
    std::string root = _generator->popRoot();
    std::vector<std::string> folder_list;
    std::vector<std::string> file_list;
    for (auto name : ftxpath::listdir(root))
    {
        if (ftxpath::isdir(name))
        {
            folder_list.push_back(name);
            _generator->pushFolder(name);
        }
        else
        {
            file_list.push_back(name);
        }
    }
    
    std::get<0>(_current) = root;
    std::get<1>(_current) = folder_list;
    std::get<2>(_current) = file_list;

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
    std::string root = _roots.back();
    root = ftxpath::join(root, folder);
    _roots.push_back(ftxpath::normpath(root));
}

std::string PathGenerator::popRoot()
{
    if (_roots.empty())
    {
        return std::string();
    }

    std::string root = _roots.back();
    _roots.pop_back();

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