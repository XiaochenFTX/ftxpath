//
//  split.cpp
//  libpath
//
//  Created by 王晓辰 on 15/8/9.
//  Copyright (c) 2015年 ftxtool. All rights reserved.
//

#include "split.h"

#include <sstream>



std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        if(!item.empty()) elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}