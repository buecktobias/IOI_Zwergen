//
// Created by tobias on 12.10.19.
//
#include <vector>
#include "Graph.h"

using namespace std;



void Graph::addNode(Node* newNode){
    this->nodes.push_back(newNode);
    this->nodes_map[newNode->name] = newNode;
}

Node* Graph::containsNode(Node* nodeTested){
    for(Node* node: this->nodes){
        if(node->name == nodeTested->name){
            return node;
        }
    }
    addNode(nodeTested);
    return nodeTested;
}

Node* Graph::getNode(const string& key) const{
    return this->nodes_map.at(key);
}

void Graph::addEdge(string& str_node1, string& str_node2, char& comparator){
    Node* node1 = new Node(str_node1);
    Node* node2 = new Node(str_node2);
    node1 = containsNode(node1);
    node2 = containsNode(node2);
    if(comparator == '>'){
        node1->addNeighbour(node2);
    }else if(comparator == '<'){
        node2->addNeighbour(node1);
    }else{
        __throw_invalid_argument("comparator is incorrect !!");
    }


}


ostream &operator<<(ostream &os, const Graph &graph) {
    string out;
    for(Node* node: graph.nodes){
        out += node->toString();
    }
    os << out;
    return os;
}



