#include <iostream>
#include <string>
#include <chrono>
#include "sys/sysinfo.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <unistd.h>
#include <unordered_map>
#include <unordered_set>
#include "Graph.h"


struct sysinfo memInfo;

using namespace std;

void measureTime(void (*f)()){
    chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    f();
    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << endl;
}



int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

int getValue(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != nullptr){
        if (strncmp(line, "VmSize:", 7) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}


int getMBSpaceConsumption(){
    int kbSpace = getValue();
    return kbSpace / 1000;
}

int getKBSpaceConsumption(){
    return getValue();
}

void measureSpace(){
    int kbSpace = getValue();
    cout << "Space Consumption = " << kbSpace << "KB, "<< kbSpace / 1000 << "MB" << endl;
}


void controlSpaceConsumption(){
    int mostMBSpaceConsumption = 0;
    int currentSpaceConsumption;
    while(true){
        currentSpaceConsumption = getMBSpaceConsumption();
        if(currentSpaceConsumption > mostMBSpaceConsumption){
            mostMBSpaceConsumption = currentSpaceConsumption;
        }
        if(currentSpaceConsumption > 400){
            cout << "More than 400 MB space consumed. ";
            break;
        }
        sleep(1);
    }
}

bool dfs(const Graph& graph, Node* currentNode, unordered_map<string,bool>& visited, unordered_set<string>& visitedBefore){
    visited[currentNode->name] = true;
    for(Node* node: currentNode->getNeighbours()){
        auto got = visitedBefore.find (node->name);
        if(got != visitedBefore.end()){
            return false;
        }
        if(visited[node->name]){
            return true;
        }
        return dfs(graph,node,visited,visitedBefore);
    }
    return false;
}


Node* nodeNotVisited(const Graph& g, const unordered_map<string, bool>& visited){
    for(pair<string,bool> kv:visited){
        if(!kv.second){
            return g.getNode(kv.first);
        }
    }
    return nullptr;
}


void addAllNodesVisitedToVisitedBefore(unordered_map<string, bool>& visited, unordered_set<string>& visitedBefore){
    for(pair<string,bool> kv:visited){
        if(kv.second){
            visitedBefore.insert(kv.first);
        }
    }
}

bool isCyclic(const Graph& g){

    unordered_map<string, bool> visited(g.nodes.size());
    for(Node* node: g.nodes){
        visited[node->name] = false;
    }
    unordered_set<string> visitedBefore;
    Node* node = nodeNotVisited(g,visited);
    while(node != nullptr){
        if(dfs(g,node,visited, visitedBefore)){
            return true;
        }
        addAllNodesVisitedToVisitedBefore(visited,visitedBefore);
        node = nodeNotVisited(g,visited);
    }
    return false;
}

void exercise(){
    // INPUT

    Graph graph = Graph();
    int amountOfComparisons;
    cin >> amountOfComparisons;
    for(int i = 0; i < amountOfComparisons; i++){
        string name1,name2;
        char comparator;
        cin >> name1;
        cin >> comparator;
        cin >> name2;
        graph.addEdge(name1,name2,comparator);
    }

    chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    string result;
    result = isCyclic(graph) ? "impossible" : "possible";
    cout << result << endl;
    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << endl;
}

void test(){
    Graph g  = Graph();
    string tobias = "Tobias";
    string martin = "Martin";
    string sebastian = "Sebastian";
    string tom = "Tom";
    string lisa = "Lisa";
    string lea = "Lea";
    string lilli = "Lilli";
    char smaller = '<';
    char bigger = '>';

    g.addEdge(tobias,martin, smaller);
    g.addEdge(tobias,lisa, bigger);
    g.addEdge(lilli,lisa, bigger);
    g.addEdge(lilli,tom, smaller);
    g.addEdge(tom,martin, smaller);
    g.addEdge(lea,lisa, bigger);
    g.addEdge(sebastian,tobias, bigger);
    cout << (isCyclic(g) ? "impossible" : "possible") << endl;
}

int main() {
    measureTime(test);
    return 0;
}