#pragma once
#include "Constants.h"

class Student 
{
private:
    string id;
    string name;
    string enrolledCourses[MAX_COURSES];
    int enrolledCount;
    string completedCourses[MAX_COURSES];
    int completedCount;
    
public:
    Student();
    Student(string id, string name);
    void enrollCourse(string course);
    void completeCourse(string course);
    
    string getId();
    string getName();
    void getEnrolledCourses(string courses[], int& count);
    void getCompletedCourses(string courses[], int& count);
    
    void display();
};