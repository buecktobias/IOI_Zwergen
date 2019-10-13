//
// Created by tobias on 12.10.19.
//
#include <vector>
#include "Node.cpp"
#include "Edge.cpp"

using namespace std;

class Graph{ // directed
public:
    vector<Node*> nodes;

    void addNode(Node* newNode){
        this->nodes.push_back(newNode);
    }

    Node* containsNode(Node* nodeTested){
        for(Node* node: this->nodes){
            if(node == nodeTested){
                return node;
            }
        }
        addNode(nodeTested);
        return nodeTested;
    }

    void addEdge(string& str_node1, string& str_node2, char& comparator){
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

    friend ostream &operator<<(ostream &os, const Graph &graph) {
        string out;
        for(Node* node: graph.nodes){
            out += node->toString();
        }
        os << out;
        return os;
    }
};


