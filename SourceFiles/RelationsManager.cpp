#include "HeaderFiles/RelationsManager.h"

RelationsManager::RelationsManager() 
{
    relationCount = 0;
}

int RelationsManager::findRelation(string name) 
{
    for(int i = 0; i < relationCount; i++)
    {
        if(relations[i].name == name)
        {
            return i;
        }
    }
    return -1;
}

void RelationsManager::addRelation(string name, string pairs[][2], int pairCount) 
{
    relations[relationCount].name = name;
    relations[relationCount].pairCount = pairCount;
    for(int i = 0; i < pairCount; i++)
    {
        relations[relationCount].pairs[i][0] = pairs[i][0];
        relations[relationCount].pairs[i][1] = pairs[i][1];
    }
    relationCount++;
}

bool RelationsManager::isReflexive(string relationName, string elements[], int elementCount) 
{
    int index = findRelation(relationName);
    if(index == -1)
    {
        return false;
    }
    
    for(int i = 0; i < elementCount; i++)
    {
        bool found = false;
        for(int j = 0; j < relations[index].pairCount; j++)
        {
            if(relations[index].pairs[j][0] == elements[i] && 
               relations[index].pairs[j][1] == elements[i])
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

bool RelationsManager::isSymmetric(string relationName) 
{
    int index = findRelation(relationName);
    if(index == -1)
    {
        return false;
    }
    
    for(int i = 0; i < relations[index].pairCount; i++)
    {
        bool found = false;
        for(int j = 0; j < relations[index].pairCount; j++)
        {
            if(relations[index].pairs[j][0] == relations[index].pairs[i][1] && 
               relations[index].pairs[j][1] == relations[index].pairs[i][0])
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

bool RelationsManager::isTransitive(string relationName) 
{
    int index = findRelation(relationName);
    if(index == -1)
    {
        return false;
    }
    
    for(int i = 0; i < relations[index].pairCount; i++)
    {
        for(int j = 0; j < relations[index].pairCount; j++)
        {
            if(relations[index].pairs[i][1] == relations[index].pairs[j][0])
            {
                bool found = false;
                for(int k = 0; k < relations[index].pairCount; k++)
                {
                    if(relations[index].pairs[k][0] == relations[index].pairs[i][0] && 
                       relations[index].pairs[k][1] == relations[index].pairs[j][1])
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
        }
    }
    return true;
}

bool RelationsManager::isEquivalence(string relationName, string elements[], int elementCount) 
{
    return isReflexive(relationName, elements, elementCount) && 
           isSymmetric(relationName) && 
           isTransitive(relationName);
}

void RelationsManager::composeRelations(string rel1, string rel2, string result[][2], int& resultCount) 
{
    int index1 = findRelation(rel1);
    int index2 = findRelation(rel2);
    resultCount = 0;
    
    if(index1 == -1 || index2 == -1)
    {
        return;
    }
    
    for(int i = 0; i < relations[index1].pairCount; i++)
    {
        for(int j = 0; j < relations[index2].pairCount; j++)
        {
            if(relations[index1].pairs[i][1] == relations[index2].pairs[j][0])
            {
                result[resultCount][0] = relations[index1].pairs[i][0];
                result[resultCount][1] = relations[index2].pairs[j][1];
                resultCount++;
            }
        }
    }
}

void RelationsManager::displayRelation(string name) 
{
    int index = findRelation(name);
    if(index == -1)
    {
        cout << "Relation not found!" << endl;
        return;
    }
    
    cout << "\nRelation " << name << " = { ";
    for(int i = 0; i < relations[index].pairCount; i++)
    {
        cout << "(" << relations[index].pairs[i][0] << "," 
             << relations[index].pairs[i][1] << ") ";
    }
    cout << "}" << endl;
}