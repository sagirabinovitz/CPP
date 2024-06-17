//
// Created by user on 14/03/2024.
//

#ifndef CPPEX02_EDGE_H
#define CPPEX02_EDGE_H

#include <string>

using namespace std;

class Edge {
public:
    string v1;
    string v2;
    double weight;
    string type;
    Edge(string v, string u, double w, string s) : v1(move(v)), v2(move(u)), weight(w),
                                                   type(move(s)) {}
};

#endif //CPPEX02_EDGE_H
