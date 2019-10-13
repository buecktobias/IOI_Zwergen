#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "sys/sysinfo.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <unistd.h>
#include "Graph.cpp"


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
        graph.addEdge(name1,name2,comparator)
    }
    cout << graph;
    //
}


int main() {
    measureTime(exercise);
    return 0;
}