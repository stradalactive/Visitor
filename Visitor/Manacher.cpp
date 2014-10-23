//
//  Manacher.cpp
//  Visitor
//
//  Created by Eric Stradal on 10/14/14.
//  Copyright (c) 2014 Eric Stradal. All rights reserved.
//

#include "Manacher.h"

Manacher::Manacher(){
    myString = new std::string("");
    myLengths = new std::vector<int>(0);
}

Manacher::Manacher(std::string *p){
    myString = new std::string(*p);
    myLengths = new std::vector<int>(p->length() * 2);
}

std::vector<int> *Manacher::go(){
    myLengths->clear();
    std::vector<int> *l = new std::vector<int>;
    int palLen = 0;
    int i = 0;
    while (i < this->myString->length()) {
        if (i > palLen) {
            char aa = this->myString->at(i - palLen - 1);
            char ab = this->myString->at(i);
            if ((i > palLen) && (aa == ab)){
                palLen += 2;
                i++;
                continue;
            }
        }
        l->push_back(palLen);
        
        int s = (int)l->size() - 2;
        int e = s - palLen;
        int d = 0, j;
        bool    found = false;
        for (j = s; j > e; j--) {
            d = j - e - 1;
            
            if (l->at(j)== d) {
                palLen = d;
                found = true;
                break;
            }
            l->push_back(d < l->at(j) ? d : l->at(j));
        }
        if ((palLen == 0) && (!found)) {
            palLen = 1;
            i++;
        }
    }
    l->push_back(palLen);
    
    int lLen = (int)l->size();
    int s = lLen - 2;
    int e = s - (2 * (int)this->myString->size() + 1 - lLen);
    for (int i=s; i>e; i--) {
        int d = i - e - 1;
        l->push_back(d < l->at(i) ? d : l->at(i));
    }
    return l;
}