#include "HeaderFiles/InductionVerifier.h"

InductionVerifier::InductionVerifier() 
{
    courseCount = 0;
    for(int i = 0; i < MAX_COURSES; i++)
    {
        chainLengths[i] = 0;
    }
}

void InductionVerifier::addPrerequisiteChain(string course, string prereqs[], int size) 
{
    courses[courseCount] = course;
    for(int i = 0; i < size; i++)
    {
        prereqChains[courseCount][i] = prereqs[i];
    }
    chainLengths[courseCount] = size;
    courseCount++;
}

bool InductionVerifier::verifyBaseCase(string course) 
{
    for(int i = 0; i < courseCount; i++)
    {
        if(courses[i] == course)
        {
            return chainLengths[i] == 0;
        }
    }
    return false;
}

bool InductionVerifier::verifyInductiveStep(string course, string completed[], int completedSize) 
{
    int courseIndex = -1;
    for(int i = 0; i < courseCount; i++)
    {
        if(courses[i] == course)
        {
            courseIndex = i;
            break;
        }
    }
    
    if(courseIndex == -1)
    {
        return false;
    }
    
    for(int i = 0; i < chainLengths[courseIndex]; i++)
    {
        bool found = false;
        for(int j = 0; j < completedSize; j++)
        {
            if(completed[j] == prereqChains[courseIndex][i])
            {
                found = true;
                break;
            }
        }
        if(!found)
        {
            return false;
        }
    }
    return true;
}

bool InductionVerifier::verifyPrerequisites(string targetCourse, string completedCourses[], int size) 
{
    cout << "\n=== Verifying Prerequisites for " << targetCourse << " ===" << endl;
    
    if(verifyBaseCase(targetCourse))
    {
        cout << "Base case: " << targetCourse << " has no prerequisites." << endl;
        return true;
    }
    
    cout << "Checking if all prerequisites are completed..." << endl;
    
    int courseIndex = -1;
    for(int i = 0; i < courseCount; i++)
    {
        if(courses[i] == targetCourse)
        {
            courseIndex = i;
            break;
        }
    }
    
    if(courseIndex == -1)
    {
        return false;
    }
    
    for(int i = 0; i < chainLengths[courseIndex]; i++)
    {
        bool found = false;
        for(int j = 0; j < size; j++)
        {
            if(completedCourses[j] == prereqChains[courseIndex][i])
            {
                found = true;
                break;
            }
        }
        
        if(found)
        {
            cout << "  * " << prereqChains[courseIndex][i] << " is completed" << endl;
        }
        else
        {
            cout << "  * " << prereqChains[courseIndex][i] << " is NOT completed" << endl;
            return false;
        }
    }
    
    cout << "All prerequisites satisfied!" << endl;
    return true;
}

void InductionVerifier::displayChain(string course) 
{
    cout << "\nPrerequisite chain for " << course << ": ";
    for(int i = 0; i < courseCount; i++)
    {
        if(courses[i] == course)
        {
            for(int j = 0; j < chainLengths[i]; j++)
            {
                cout << prereqChains[i][j] << " ";
            }
            break;
        }
    }
    cout << endl;
}