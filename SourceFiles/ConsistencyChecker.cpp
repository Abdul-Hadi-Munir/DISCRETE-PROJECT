#include "HeaderFiles/ConsistencyChecker.h"

ConsistencyChecker::ConsistencyChecker() 
{
    conflictCount = 0;
}

bool ConsistencyChecker::checkStudentOverload(string student, int maxCourses, int courseCount) 
{
    if(courseCount > maxCourses)
    {
        string conflict = student + " is overloaded with " + to_string(courseCount) + " courses";
        conflicts[conflictCount] = conflict;
        conflictCount++;
        return false;
    }
    return true;
}

void ConsistencyChecker::displayConflicts() 
{
    cout << "\n=== Consistency Conflicts ===" << endl;
    if(conflictCount == 0)
    {
        cout << "No conflicts found." << endl;
    }
    else
    {
        for(int i = 0; i < conflictCount; i++)
        {
            cout << "  * " << conflicts[i] << endl;
        }
    }
}

void ConsistencyChecker::clearConflicts() 
{
    conflictCount = 0;
}