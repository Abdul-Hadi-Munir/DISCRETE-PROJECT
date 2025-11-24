#pragma once
#include "Constants.h"

class CourseScheduler 
{
private:
    string courseNames[MAX_COURSES];
    string prereqList[MAX_COURSES][MAX_PREREQS];
    int prereqCount[MAX_COURSES];
    int courseCount;
    
    string sequences[MAX_SEQUENCES][MAX_COURSES];
    int sequenceLengths[MAX_SEQUENCES];
    int sequenceCount;
    
    void generateSequencesHelper(string current[], int currentSize, bool completed[], string remaining[], int remainingSize);
    
public:
    CourseScheduler();
    void addPrerequisite(string course, string prereq);
    void generateAllValidSequences(string courses[], int size);
    void displaySequences();
};