#include "HeaderFiles/Faculty.h"

Faculty::Faculty() 
{
    id = "";
    name = "";
    courseCount = 0;
}

Faculty::Faculty(string id, string name) 
{
    this->id = id;
    this->name = name;
    courseCount = 0;
}

void Faculty::assignCourse(string course) 
{
    assignedCourses[courseCount] = course;
    courseCount++;
}

string Faculty::getId() 
{
    return id;
}

string Faculty::getName() 
{
    return name;
}

void Faculty::display() 
{
    cout << "Faculty ID: " << id << ", Name: " << name << endl;
    cout << "Assigned Courses: ";
    for(int i = 0; i < courseCount; i++)
    {
        cout << assignedCourses[i] << " ";
    }
    cout << endl;
}