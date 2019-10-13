//
// Created by tobias on 13.10.19.
//

#ifndef IOI_ZWERGEN_EDGE_H
#define IOI_ZWERGEN_EDGE_H

#include <string>
using namespace std;

struct Edge{
    Edge();
    Edge(string& n1,string& n2, char& comparator);
    string name1;
    string name2;
    char comparator;
};


#endif //IOI_ZWERGEN_EDGE_H
