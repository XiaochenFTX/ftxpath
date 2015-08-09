//
//  split.h
//  libpath
//
//  Created by 王晓辰 on 15/8/9.
//  Copyright (c) 2015年 ftxtool. All rights reserved.
//

#ifndef libpath_split_h
#define libpath_split_h

#include <vector>
#include <string>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

#endif
