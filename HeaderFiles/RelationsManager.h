#pragma once
#include "Constants.h"

class RelationsManager 
{
private:
    struct Relation 
    {
        string name;
        string pairs[MAX_SIZE][2];
        int pairCount;
    };
    
    Relation relations[MAX_RELATIONS];
    int relationCount;
    
    int findRelation(string name);
    
public:
    RelationsManager();
    void addRelation(string name, string pairs[][2], int pairCount);
    bool isReflexive(string relationName, string elements[], int elementCount);
    bool isSymmetric(string relationName);
    bool isTransitive(string relationName);
    bool isEquivalence(string relationName, string elements[], int elementCount);
    void composeRelations(string rel1, string rel2, string result[][2], int& resultCount);
    void displayRelation(string name);
};