//
// Created by tobias on 13.10.19.
//

#ifndef IOI_ZWERGEN_NODE_H
#define IOI_ZWERGEN_NODE_H

#include <string>
#include <vector>
#include <list>
#include "Edge.h"

using namespace std;

struct Node{
    string name;
    list<Edge> edges;
    list<Node*> neighbours;
    void addNeighbour(Node* node);
    explicit Node(string name);
    [[nodiscard]] list<Node*> getNeighbours() const;
    void addEdge(const Edge& newEdge);
    bool operator==(const Node &rhs) const;
    [[nodiscard]] string toString() const;
    friend ostream &operator<<(ostream &os, const Node &node);
};

#endif //IOI_ZWERGEN_NODE_H
