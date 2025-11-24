#include "HeaderFiles/Student.h"

Student::Student() 
{
    id = "";
    name = "";
    enrolledCount = 0;
    completedCount = 0;
}

Student::Student(string id, string name) 
{
    this->id = id;
    this->name = name;
    enrolledCount = 0;
    completedCount = 0;
}

void Student::enrollCourse(string course) 
{
    enrolledCourses[enrolledCount] = course;
    enrolledCount++;
}

void Student::completeCourse(string course) 
{
    completedCourses[completedCount] = course;
    completedCount++;
    
    for(int i = 0; i < enrolledCount; i++)
    {
        if(enrolledCourses[i] == course)
        {
            for(int j = i; j < enrolledCount - 1; j++)
            {
                enrolledCourses[j] = enrolledCourses[j + 1];
            }
            enrolledCount--;
            break;
        }
    }
}

string Student::getId() 
{
    return id;
}

string Student::getName() 
{
    return name;
}

void Student::getEnrolledCourses(string courses[], int& count) 
{
    count = enrolledCount;
    for(int i = 0; i < enrolledCount; i++)
    {
        courses[i] = enrolledCourses[i];
    }
}

void Student::getCompletedCourses(string courses[], int& count) 
{
    count = completedCount;
    for(int i = 0; i < completedCount; i++)
    {
        courses[i] = completedCourses[i];
    }
}

void Student::display() 
{
    cout << "Student ID: " << id << ", Name: " << name << endl;
    cout << "  Enrolled: ";
    for(int i = 0; i < enrolledCount; i++)
    {
        cout << enrolledCourses[i] << " ";
    }
    cout << "\n  Completed: ";
    for(int i = 0; i < completedCount; i++)
    {
        cout << completedCourses[i] << " ";
    }
    cout << endl;
}