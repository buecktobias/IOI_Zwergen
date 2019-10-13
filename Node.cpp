//
// Created by tobias on 12.10.19.
//
#include <string>
#include <utility>
#include <vector>
#include "Node.h"


using namespace std;

[[nodiscard]] vector<Node*> Node::getNeighbours() const{
    vector<Node*> result;
    for(Edge edge: this->edges){
        if(edge.from == this){
            result.push_back(edge.to);
        }
    }
    return result;
}
Node::Node(string name):name(std::move(name)) {}

void Node::addEdge(const Edge& newEdge){
    this->edges.push_back(newEdge);
}

bool Node::operator==(const Node &rhs) const {
    return name == rhs.name;
}

[[nodiscard]] string Node::toString() const {
    string nodesString;
    vector<Node*> neighbours = this->getNeighbours();
    for(unsigned long i = 0; i < neighbours.size(); i++){
        nodesString += neighbours[i]->name;
        if(i != neighbours.size()-1){
            nodesString += ", ";
        }
    }
    return this->name + "-> " + nodesString + "\n";
}

ostream &operator<<(ostream &os, const Node &node) {
    os << node.toString();
    return os;
}


