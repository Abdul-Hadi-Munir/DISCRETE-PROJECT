#include "HeaderFiles/GroupManager.h"
#include "HeaderFiles/Student.h"

GroupManager::GroupManager() 
{
    studentCount = 0;
    groupCount = 0;
}

void GroupManager::addStudent(Student* s) 
{
    students[studentCount] = s;
    studentCount++;
}

void GroupManager::generateCombinationsHelper(int start, int groupSize, 
                                             Student* current[], int currentSize) 
{
    if(currentSize == groupSize)
    {
        for(int i = 0; i < groupSize; i++)
        {
            groups[groupCount][i] = current[i];
        }
        groupSizes[groupCount] = groupSize;
        groupCount++;
        return;
    }
    
    for(int i = start; i < studentCount; i++)
    {
        current[currentSize] = students[i];
        generateCombinationsHelper(i + 1, groupSize, current, currentSize + 1);
    }
}

void GroupManager::generateGroups(int groupSize) 
{
    groupCount = 0;
    Student* current[MAX_STUDENTS];
    generateCombinationsHelper(0, groupSize, current, 0);
}

int GroupManager::calculateCombinations(int n, int r) 
{
    if(r > n)
    {
        return 0;
    }
    if(r == 0 || r == n)
    {
        return 1;
    }
    
    int result = 1;
    for(int i = 0; i < r; i++)
    {
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}

void GroupManager::displayGroups() 
{
    cout << "\n=== Student Groups ===" << endl;
    cout << "Total groups: " << groupCount << endl;
    for(int i = 0; i < groupCount; i++)
    {
        cout << "Group " << (i + 1) << ": ";
        for(int j = 0; j < groupSizes[i]; j++)
        {
            cout << groups[i][j]->getName() << " ";
        }
        cout << endl;
    }
}