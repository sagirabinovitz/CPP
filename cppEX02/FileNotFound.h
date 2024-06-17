//
// Created by user on 14/03/2024.
//

#ifndef CPPEX02_FILENOTFOUND_H
#define CPPEX02_FILENOTFOUND_H

#include <iostream>


using namespace std;

class FileNotFound : invalid_argument {
public:
    explicit FileNotFound(const string& str) : invalid_argument(str){};

};


#endif //CPPEX02_FILENOTFOUND_H
