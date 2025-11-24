#pragma once
#include "Constants.h"

class Faculty 
{
private:
    string id;
    string name;
    string assignedCourses[MAX_COURSES];
    int courseCount;
    
public:
    Faculty();
    Faculty(string id, string name);
    void assignCourse(string course);
    
    string getId();
    string getName();
    
    void display();
};