#include "HeaderFiles/LogicEngine.h"

LogicEngine::LogicEngine() 
{
    ruleCount = 0;
    factCount = 0;
}

int LogicEngine::findFact(string fact) 
{
    for(int i = 0; i < factCount; i++)
    {
        if(factNames[i] == fact)
        {
            return i;
        }
    }
    return -1;
}

void LogicEngine::addRule(string condition, string conclusion, string type) 
{
    rules[ruleCount].condition = condition;
    rules[ruleCount].conclusion = conclusion;
    rules[ruleCount].type = type;
    ruleCount++;
}

void LogicEngine::addFact(string fact, bool value) 
{
    int index = findFact(fact);
    if(index == -1)
    {
        factNames[factCount] = fact;
        factValues[factCount] = value;
        factCount++;
    }
    else
    {
        factValues[index] = value;
    }
}

bool LogicEngine::evaluate(string query) 
{
    int index = findFact(query);
    if(index != -1)
    {
        return factValues[index];
    }
    return false;
}

void LogicEngine::performInference() 
{
    cout << "\n=== Performing Inference ===" << endl;
    bool changed = true;
    int iterations = 0;
    
    while(changed && iterations < 10)
    {
        changed = false;
        for(int i = 0; i < ruleCount; i++)
        {
            int condIndex = findFact(rules[i].condition);
            int concIndex = findFact(rules[i].conclusion);
            
            if(concIndex == -1)
            {
                addFact(rules[i].conclusion, false);
                concIndex = factCount - 1;
            }
            
            if(condIndex != -1 && factValues[condIndex] && !factValues[concIndex])
            {
                factValues[concIndex] = true;
                cout << "Inferred: " << rules[i].conclusion << " from " << rules[i].condition << endl;
                changed = true;
            }
        }
        iterations++;
    }
}

void LogicEngine::displayRules() 
{
    cout << "\n=== Logic Rules ===" << endl;
    for(int i = 0; i < ruleCount; i++)
    {
        cout << rules[i].condition << " => " << rules[i].conclusion 
             << " [" << rules[i].type << "]" << endl;
    }
}