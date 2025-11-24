#pragma once
#include "Constants.h"

class FunctionsManager 
{
private:
    struct Function 
    {
        string name;
        string domain[MAX_SIZE];
        string codomain[MAX_SIZE];
        int mappingCount;
    };
    
    Function functions[MAX_FUNCTIONS];
    int functionCount;
    
    int findFunction(string name);
    
public:
    FunctionsManager();
    void addFunction(string name, string domain[], string codomain[], int size);
    bool isInjective(string funcName);
    bool isSurjective(string funcName, string codomain[], int codomainSize);
    bool isBijective(string funcName, string codomain[], int codomainSize);
    void composeFunctions(string func1, string func2, string resultDomain[], string resultCodomain[], int& resultSize);
    void inverseFunction(string funcName, string resultDomain[], string resultCodomain[], int& resultSize);
    void displayFunction(string name);
};