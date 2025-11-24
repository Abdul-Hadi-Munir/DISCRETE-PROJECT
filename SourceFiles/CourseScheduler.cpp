#include "HeaderFiles/CourseScheduler.h"

CourseScheduler::CourseScheduler() 
{
    courseCount = 0;
    sequenceCount = 0;
    for(int i = 0; i < MAX_COURSES; i++)
    {
        prereqCount[i] = 0;
        sequenceLengths[i] = 0;
    }
}

void CourseScheduler::addPrerequisite(string course, string prereq) 
{
    int courseIndex = -1;
    for(int i = 0; i < courseCount; i++)
    {
        if(courseNames[i] == course)
        {
            courseIndex = i;
            break;
        }
    }
    
    if(courseIndex == -1)
    {
        courseIndex = courseCount;
        courseNames[courseCount] = course;
        courseCount++;
    }
    
    prereqList[courseIndex][prereqCount[courseIndex]] = prereq;
    prereqCount[courseIndex]++;
}

void CourseScheduler::generateSequencesHelper(string current[], int currentSize, 
                                             bool completed[], string remaining[], int remainingSize) 
{
    if(remainingSize == 0)
    {
        for(int i = 0; i < currentSize; i++)
        {
            sequences[sequenceCount][i] = current[i];
        }
        sequenceLengths[sequenceCount] = currentSize;
        sequenceCount++;
        return;
    }
    
    for(int i = 0; i < remainingSize; i++)
    {
        string course = remaining[i];
        bool canTake = true;
        
        int courseIndex = -1;
        for(int j = 0; j < courseCount; j++)
        {
            if(courseNames[j] == course)
            {
                courseIndex = j;
                break;
            }
        }
        
        if(courseIndex != -1)
        {
            for(int j = 0; j < prereqCount[courseIndex]; j++)
            {
                bool found = false;
                for(int k = 0; k < currentSize; k++)
                {
                    if(current[k] == prereqList[courseIndex][j])
                    {
                        found = true;
                        break;
                    }
                }
                if(!found)
                {
                    canTake = false;
                    break;
                }
            }
        }
        
        if(canTake)
        {
            current[currentSize] = course;
            
            string newRemaining[MAX_COURSES];
            int newRemainingSize = 0;
            for(int j = 0; j < remainingSize; j++)
            {
                if(j != i)
                {
                    newRemaining[newRemainingSize] = remaining[j];
                    newRemainingSize++;
                }
            }
            
            generateSequencesHelper(current, currentSize + 1, completed, newRemaining, newRemainingSize);
        }
    }
}

void CourseScheduler::generateAllValidSequences(string courses[], int size) 
{
    sequenceCount = 0;
    string current[MAX_COURSES];
    bool completed[MAX_COURSES];
    
    for(int i = 0; i < MAX_COURSES; i++)
    {
        completed[i] = false;
    }
    
    generateSequencesHelper(current, 0, completed, courses, size);
}

void CourseScheduler::displaySequences() 
{
    cout << "\n=== Valid Course Sequences ===" << endl;
    for(int i = 0; i < sequenceCount; i++)
    {
        cout << "Sequence " << (i + 1) << ": ";
        for(int j = 0; j < sequenceLengths[i]; j++)
        {
            cout << sequences[i][j] << " -> ";
        }
        cout << "END" << endl;
    }
}