//
// Created by tobias on 13.10.19.
//

#ifndef IOI_ZWERGEN_GRAPH_H
#define IOI_ZWERGEN_GRAPH_H
#include "Node.h"
#include <vector>
#include <unordered_map>

using namespace std;
struct Graph{
    unordered_map<string, Node*> nodes_map;
    Node* getNode(const string& key) const;
    vector<Node*> getNodes() const;
    void addNode(Node* newNode);
    Node* containsNode(Node* nodeTested);
    void addEdge(string& str_node1, string& str_node2, char& comparator);
    friend ostream &operator<<(ostream &os, const Graph &graph);
};
#endif //IOI_ZWERGEN_GRAPH_H
