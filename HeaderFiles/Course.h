#pragma once
#include "Constants.h"

class Course 
{
private:
    string code;
    string name;
    string prerequisites[MAX_PREREQS];
    int prereqCount;
    int credits;
    
public:
    Course();
    Course(string code, string name, int credits);
    void addPrerequisite(string prereq);
    
    string getCode();
    string getName();
    void getPrerequisites(string prereqs[], int& count);
    
    void display();
};