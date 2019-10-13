//
// Created by tobias on 13.10.19.
//

#include "Edge.h"
Edge::Edge(string& n1, string& n2, char& comparator) : name1(n1), name2(n2), comparator(comparator){

}
Edge::Edge(){
    comparator = '=';
    name1 = "";
    name2 = "";
}