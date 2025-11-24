#pragma once
#include "Constants.h"
#include "Student.h" // Required because it uses Student*

class GroupManager 
{
private:
    Student* students[MAX_STUDENTS];
    int studentCount;
    
    Student* groups[MAX_GROUPS][MAX_STUDENTS];
    int groupSizes[MAX_GROUPS];
    int groupCount;
    
    void generateCombinationsHelper(int start, int groupSize, Student* current[], int currentSize);
    
public:
    GroupManager();
    void addStudent(Student* s);
    void generateGroups(int groupSize);
    void displayGroups();
    int calculateCombinations(int n, int r);
};