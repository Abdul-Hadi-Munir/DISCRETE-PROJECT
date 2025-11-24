#include "HeaderFiles/FunctionsManager.h"

FunctionsManager::FunctionsManager() 
{
    functionCount = 0;
}

int FunctionsManager::findFunction(string name) 
{
    for(int i = 0; i < functionCount; i++)
    {
        if(functions[i].name == name)
        {
            return i;
        }
    }
    return -1;
}

void FunctionsManager::addFunction(string name, string domain[], string codomain[], int size) 
{
    functions[functionCount].name = name;
    functions[functionCount].mappingCount = size;
    for(int i = 0; i < size; i++)
    {
        functions[functionCount].domain[i] = domain[i];
        functions[functionCount].codomain[i] = codomain[i];
    }
    functionCount++;
}

bool FunctionsManager::isInjective(string funcName) 
{
    int index = findFunction(funcName);
    if(index == -1)
    {
        return false;
    }
    
    for(int i = 0; i < functions[index].mappingCount; i++)
    {
        for(int j = i + 1; j < functions[index].mappingCount; j++)
        {
            if(functions[index].codomain[i] == functions[index].codomain[j])
            {
                return false;
            }
        }
    }
    return true;
}

bool FunctionsManager::isSurjective(string funcName, string codomain[], int codomainSize) 
{
    int index = findFunction(funcName);
    if(index == -1)
    {
        return false;
    }
    
    for(int i = 0; i < codomainSize; i++)
    {
        bool found = false;
        for(int j = 0; j < functions[index].mappingCount; j++)
        {
            if(functions[index].codomain[j] == codomain[i])
            {
                found = true;
                break;
            }
        }
        if(!found)
        {
            return false;
        }
    }
    return true;
}

bool FunctionsManager::isBijective(string funcName, string codomain[], int codomainSize) 
{
    return isInjective(funcName) && isSurjective(funcName, codomain, codomainSize);
}

void FunctionsManager::composeFunctions(string func1, string func2, string resultDomain[], 
                                       string resultCodomain[], int& resultSize) 
{
    int index1 = findFunction(func1);
    int index2 = findFunction(func2);
    resultSize = 0;
    
    if(index1 == -1 || index2 == -1)
    {
        return;
    }
    
    for(int i = 0; i < functions[index1].mappingCount; i++)
    {
        for(int j = 0; j < functions[index2].mappingCount; j++)
        {
            if(functions[index1].codomain[i] == functions[index2].domain[j])
            {
                resultDomain[resultSize] = functions[index1].domain[i];
                resultCodomain[resultSize] = functions[index2].codomain[j];
                resultSize++;
            }
        }
    }
}

void FunctionsManager::inverseFunction(string funcName, string resultDomain[], 
                                      string resultCodomain[], int& resultSize) 
{
    int index = findFunction(funcName);
    resultSize = 0;
    
    if(index == -1 || !isInjective(funcName))
    {
        return;
    }
    
    for(int i = 0; i < functions[index].mappingCount; i++)
    {
        resultDomain[resultSize] = functions[index].codomain[i];
        resultCodomain[resultSize] = functions[index].domain[i];
        resultSize++;
    }
}

void FunctionsManager::displayFunction(string name) 
{
    int index = findFunction(name);
    if(index == -1)
    {
        cout << "Function not found!" << endl;
        return;
    }
    
    cout << "\nFunction " << name << ":" << endl;
    for(int i = 0; i < functions[index].mappingCount; i++)
    {
        cout << "  " << functions[index].domain[i] << " -> " 
             << functions[index].codomain[i] << endl;
    }
}