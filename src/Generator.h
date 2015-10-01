//
//  Generator.h
//  libpath
//
//  Created by 王晓辰 on 15/8/16.
//  Copyright (c) 2015年 ftxtool. All rights reserved.
//

#ifndef __libpath__Generator__
#define __libpath__Generator__

#include <cstdlib>
#include <tuple>
#include <string>
#include <vector>


class PathGenerator
{
public:
    typedef std::tuple<std::string, std::vector<std::string>, std::vector<std::string>> PathTuple;

    class PathIterator
    {
    public:
        PathIterator(PathGenerator* generator);
    
        PathIterator& operator++();
        bool operator!=(const PathIterator& it);
        const PathTuple& operator*();
        
    private:
        const PathTuple& next();
        
    private:
        PathTuple _current;
        PathGenerator* _generator;
    };
    
    PathGenerator(const std::string& path);
    const PathIterator& begin();
    const PathIterator& end();
    
private:
    void pushFolder(const std::string& folder);
    std::string popRoot();
    bool empty();

private:
    std::vector<std::string> _roots;
    PathIterator _current;
};

#endif /* defined(__libpath__Generator__) */
