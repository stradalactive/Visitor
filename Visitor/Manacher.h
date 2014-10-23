//
//  Manacher.h
//  Visitor
//
//  Created by Eric Stradal on 10/14/14.
//  Copyright (c) 2014 Eric Stradal. All rights reserved.
//

#ifndef __Visitor__Manacher__
#define __Visitor__Manacher__

#include <stdio.h>
#include <iostream>
#include <vector>

class Manacher{
private:
    std::string *myString;
    std::vector<int> *myLengths;
public:
    Manacher();
    Manacher(std::string *p);
    std::vector<int> *go();
};

#endif /* defined(__Visitor__Manacher__) */
