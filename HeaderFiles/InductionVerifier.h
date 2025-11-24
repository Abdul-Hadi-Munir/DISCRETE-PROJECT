#pragma once
#include "Constants.h"

class InductionVerifier 
{
private:
    string courses[MAX_COURSES];
    string prereqChains[MAX_COURSES][MAX_PREREQS];
    int chainLengths[MAX_COURSES];
    int courseCount;
    
    bool verifyBaseCase(string course);
    bool verifyInductiveStep(string course, string completed[], int completedSize);
    
public:
    InductionVerifier();
    void addPrerequisiteChain(string course, string prereqs[], int size);
    bool verifyPrerequisites(string targetCourse, string completedCourses[], int size);
    void displayChain(string course);
};