#include "HeaderFiles/Course.h"

Course::Course() 
{
    code = "";
    name = "";
    credits = 0;
    prereqCount = 0;
}

Course::Course(string code, string name, int credits) 
{
    this->code = code;
    this->name = name;
    this->credits = credits;
    prereqCount = 0;
}

void Course::addPrerequisite(string prereq) 
{
    prerequisites[prereqCount] = prereq;
    prereqCount++;
}

string Course::getCode() 
{
    return code;
}

string Course::getName() 
{
    return name;
}

void Course::getPrerequisites(string prereqs[], int& count) 
{
    count = prereqCount;
    for(int i = 0; i < prereqCount; i++)
    {
        prereqs[i] = prerequisites[i];
    }
}

void Course::display() 
{
    cout << "Course: " << code << " - " << name << " (" << credits << " credits)" << endl;
    
    if(prereqCount > 0)
    {
        cout << "  Prerequisites: ";
        for(int i = 0; i < prereqCount; i++)
        {
            cout << prerequisites[i] << " ";
        }
        cout << endl;
    }
}