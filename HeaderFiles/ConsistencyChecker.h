#pragma once
#include "Constants.h"

class ConsistencyChecker 
{
private:
    string conflicts[MAX_CONFLICTS];
    int conflictCount;
    
public:
    ConsistencyChecker();
    bool checkStudentOverload(string student, int maxCourses, int courseCount);
    void displayConflicts();
    void clearConflicts();
};