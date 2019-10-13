//
// Created by tobias on 12.10.19.
//
#include <string>
#include <utility>
#include "Node.h"


using namespace std;

[[nodiscard]] unordered_set<Node*> Node::getNeighbours() const{
    return neighbours;
}
Node::Node(string name):name(std::move(name)) {}

void Node::addNeighbour(Node *node) {
    this->neighbours.insert(node);
}


bool Node::operator==(const Node &rhs) const {
    return name == rhs.name;
}

[[nodiscard]] string Node::toString() const {
    string nodesString;
    unordered_set<Node*> neighbours = this->getNeighbours();
    for(Node* node: neighbours){
        nodesString += node->name;
        nodesString += ", ";
    }
    return this->name + "-> " + nodesString + "\n";
}

ostream &operator<<(ostream &os, const Node &node) {
    os << node.toString();
    return os;
}


