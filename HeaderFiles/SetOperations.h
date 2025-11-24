#pragma once
#include "Constants.h"

class SetOperations 
{
private:
    string setNames[MAX_SETS];
    string setElements[MAX_SETS][MAX_SIZE];
    int setElementCounts[MAX_SETS];
    int setCount;
    
    int findSet(string name);
    
public:
    SetOperations();
    void createSet(string name, string elements[], int size);
    void unionSets(string set1, string set2, string result[], int& resultSize);
    void intersectionSets(string set1, string set2, string result[], int& resultSize);
    void differenceSets(string set1, string set2, string result[], int& resultSize);
    void powerSet(string setName, string result[][MAX_SIZE], int resultSizes[], int& resultCount);
    bool isSubset(string set1, string set2);
    void displaySet(string setName);
};