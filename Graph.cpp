//
// Created by tobias on 12.10.19.
//
#include <vector>
#include "Graph.h"

using namespace std;


vector<Node*> nodes;

void Graph::addNode(Node* newNode){
    this->nodes.push_back(newNode);
}

Node* Graph::containsNode(Node* nodeTested){
    for(Node* node: this->nodes){
        if(node == nodeTested){
            return node;
        }
    }
    addNode(nodeTested);
    return nodeTested;
}

void Graph::addEdge(string& str_node1, string& str_node2, char& comparator){
    Node* node1 = new Node(str_node1);
    Node* node2 = new Node(str_node2);
    node1 = containsNode(node1);
    node2 = containsNode(node2);

    Edge newEdge = Edge();
    if(comparator == '>'){
        newEdge.from = node1;
        newEdge.to = node2;
    }else if(comparator == '<'){
        newEdge.from = node2;
        newEdge.to = node1;
    }else{
        __throw_invalid_argument("comparator is incorrect !!");
    }
    node1->addEdge(newEdge);
    node2->addEdge(newEdge);
}

ostream &operator<<(ostream &os, const Graph &graph) {
    string out;
    for(Node* node: graph.nodes){
        out += node->toString();
    }
    os << out;
    return os;
}



