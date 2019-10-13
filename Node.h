//
// Created by tobias on 13.10.19.
//

#ifndef IOI_ZWERGEN_NODE_H
#define IOI_ZWERGEN_NODE_H

#include <string>
#include <vector>
#include <list>
#include <unordered_set>


using namespace std;

struct Node{
    string name;
    unordered_set<Node*> neighbours;
    void addNeighbour(Node* node);
    explicit Node(string name);
    [[nodiscard]] unordered_set<Node*> getNeighbours() const;
    bool operator==(const Node &rhs) const;
    [[nodiscard]] string toString() const;
    friend ostream &operator<<(ostream &os, const Node &node);
};

#endif //IOI_ZWERGEN_NODE_H
