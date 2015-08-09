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

namespace ftxpath {
    
    std::string cwd();
    
    bool isabs(const std::string&);
    
    std::string join(const std::string&, const std::string&);
    std::string join(const std::string&, const std::vector<std::string>&);
    
    std::string basename(const std::string&);
    std::string dirname(const std::string&);
    
    std::tuple<std::string, std::string> split(const std::string&);
    
}

#endif /* defined(__libpath__libpath__) */
