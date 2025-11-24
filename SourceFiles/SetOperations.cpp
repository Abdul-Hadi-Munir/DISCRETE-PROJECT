#include "HeaderFiles/SetOperations.h"

SetOperations::SetOperations() 
{
    setCount = 0;
}

int SetOperations::findSet(string name) 
{
    for(int i = 0; i < setCount; i++)
    {
        if(setNames[i] == name)
        {
            return i;
        }
    }
    return -1;
}

void SetOperations::createSet(string name, string elements[], int size) 
{
    int index = findSet(name);
    if(index == -1)
    {
        index = setCount;
        setNames[setCount] = name;
        setCount++;
    }
    
    setElementCounts[index] = size;
    for(int i = 0; i < size; i++)
    {
        setElements[index][i] = elements[i];
    }
}

void SetOperations::unionSets(string set1, string set2, string result[], int& resultSize) 
{
    int index1 = findSet(set1);
    int index2 = findSet(set2);
    resultSize = 0;
    
    if(index1 == -1 || index2 == -1)
    {
        return;
    }
    
    for(int i = 0; i < setElementCounts[index1]; i++)
    {
        result[resultSize] = setElements[index1][i];
        resultSize++;
    }
    
    for(int i = 0; i < setElementCounts[index2]; i++)
    {
        bool found = false;
        for(int j = 0; j < resultSize; j++)
        {
            if(result[j] == setElements[index2][i])
            {
                found = true;
                break;
            }
        }
        if(!found)
        {
            result[resultSize] = setElements[index2][i];
            resultSize++;
        }
    }
}

void SetOperations::intersectionSets(string set1, string set2, string result[], int& resultSize) 
{
    int index1 = findSet(set1);
    int index2 = findSet(set2);
    resultSize = 0;
    
    if(index1 == -1 || index2 == -1)
    {
        return;
    }
    
    for(int i = 0; i < setElementCounts[index1]; i++)
    {
        for(int j = 0; j < setElementCounts[index2]; j++)
        {
            if(setElements[index1][i] == setElements[index2][j])
            {
                result[resultSize] = setElements[index1][i];
                resultSize++;
                break;
            }
        }
    }
}

void SetOperations::differenceSets(string set1, string set2, string result[], int& resultSize) 
{
    int index1 = findSet(set1);
    int index2 = findSet(set2);
    resultSize = 0;
    
    if(index1 == -1 || index2 == -1)
    {
        return;
    }
    
    for(int i = 0; i < setElementCounts[index1]; i++)
    {
        bool found = false;
        for(int j = 0; j < setElementCounts[index2]; j++)
        {
            if(setElements[index1][i] == setElements[index2][j])
            {
                found = true;
                break;
            }
        }
        if(!found)
        {
            result[resultSize] = setElements[index1][i];
            resultSize++;
        }
    }
}

void SetOperations::powerSet(string setName, string result[][MAX_SIZE], int resultSizes[], int& resultCount) 
{
    int index = findSet(setName);
    if(index == -1)
    {
        resultCount = 0;
        return;
    }
    
    int n = setElementCounts[index];
    int powerSetSize = (int)pow(2, n);
    resultCount = 0;
    
    for(int i = 0; i < powerSetSize; i++)
    {
        resultSizes[resultCount] = 0;
        for(int j = 0; j < n; j++)
        {
            if(i & (1 << j))
            {
                result[resultCount][resultSizes[resultCount]] = setElements[index][j];
                resultSizes[resultCount]++;
            }
        }
        resultCount++;
    }
}

bool SetOperations::isSubset(string set1, string set2) 
{
    int index1 = findSet(set1);
    int index2 = findSet(set2);
    
    if(index1 == -1 || index2 == -1)
    {
        return false;
    }
    
    for(int i = 0; i < setElementCounts[index1]; i++)
    {
        bool found = false;
        for(int j = 0; j < setElementCounts[index2]; j++)
        {
            if(setElements[index1][i] == setElements[index2][j])
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

void SetOperations::displaySet(string setName) 
{
    int index = findSet(setName);
    if(index == -1)
    {
        cout << "Set not found!" << endl;
        return;
    }
    
    cout << setName << " = { ";
    for(int i = 0; i < setElementCounts[index]; i++)
    {
        cout << setElements[index][i] << " ";
    }
    cout << "}" << endl;
}