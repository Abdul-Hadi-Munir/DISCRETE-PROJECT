#pragma once
#include "Constants.h"

class LogicEngine 
{
private:
    struct Rule 
    {
        string condition;
        string conclusion;
        string type;
    };
    
    Rule rules[MAX_RULES];
    int ruleCount;
    
    string factNames[MAX_SIZE];
    bool factValues[MAX_SIZE];
    int factCount;
    
    int findFact(string fact);
    
public:
    LogicEngine();
    void addRule(string condition, string conclusion, string type);
    void addFact(string fact, bool value);
    bool evaluate(string query);
    void performInference();
    void displayRules();
};