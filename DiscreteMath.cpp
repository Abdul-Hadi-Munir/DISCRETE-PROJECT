#include "DiscreteMath.h"

// ============= COURSE SCHEDULER IMPLEMENTATION =============
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

// ============= GROUP MANAGER IMPLEMENTATION =============
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

// ============= INDUCTION VERIFIER IMPLEMENTATION =============
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

// ============= LOGIC ENGINE IMPLEMENTATION =============
LogicEngine::LogicEngine() 
{
    ruleCount = 0;
    factCount = 0;
}

int LogicEngine::findFact(string fact) 
{
    for(int i = 0; i < factCount; i++)
    {
        if(factNames[i] == fact)
        {
            return i;
        }
    }
    return -1;
}

void LogicEngine::addRule(string condition, string conclusion, string type) 
{
    rules[ruleCount].condition = condition;
    rules[ruleCount].conclusion = conclusion;
    rules[ruleCount].type = type;
    ruleCount++;
}

void LogicEngine::addFact(string fact, bool value) 
{
    int index = findFact(fact);
    if(index == -1)
    {
        factNames[factCount] = fact;
        factValues[factCount] = value;
        factCount++;
    }
    else
    {
        factValues[index] = value;
    }
}

bool LogicEngine::evaluate(string query) 
{
    int index = findFact(query);
    if(index != -1)
    {
        return factValues[index];
    }
    return false;
}

void LogicEngine::performInference() 
{
    cout << "\n=== Performing Inference ===" << endl;
    bool changed = true;
    int iterations = 0;
    
    while(changed && iterations < 10)
    {
        changed = false;
        for(int i = 0; i < ruleCount; i++)
        {
            int condIndex = findFact(rules[i].condition);
            int concIndex = findFact(rules[i].conclusion);
            
            if(concIndex == -1)
            {
                addFact(rules[i].conclusion, false);
                concIndex = factCount - 1;
            }
            
            if(condIndex != -1 && factValues[condIndex] && !factValues[concIndex])
            {
                factValues[concIndex] = true;
                cout << "Inferred: " << rules[i].conclusion << " from " << rules[i].condition << endl;
                changed = true;
            }
        }
        iterations++;
    }
}

void LogicEngine::displayRules() 
{
    cout << "\n=== Logic Rules ===" << endl;
    for(int i = 0; i < ruleCount; i++)
    {
        cout << rules[i].condition << " => " << rules[i].conclusion 
             << " [" << rules[i].type << "]" << endl;
    }
}

// ============= SET OPERATIONS IMPLEMENTATION =============
SetOperations::SetOperations() 
{
    setCount = 0;
}

int SetOperations::findSet(string name) 
{
    for(int i = 0; i < setCount; i++)
    {
        if(setNames[i] == name)
        {
            return i;
        }
    }
    return -1;
}

void SetOperations::createSet(string name, string elements[], int size) 
{
    int index = findSet(name);
    if(index == -1)
    {
        index = setCount;
        setNames[setCount] = name;
        setCount++;
    }
    
    setElementCounts[index] = size;
    for(int i = 0; i < size; i++)
    {
        setElements[index][i] = elements[i];
    }
}

void SetOperations::unionSets(string set1, string set2, string result[], int& resultSize) 
{
    int index1 = findSet(set1);
    int index2 = findSet(set2);
    resultSize = 0;
    
    if(index1 == -1 || index2 == -1)
    {
        return;
    }
    
    for(int i = 0; i < setElementCounts[index1]; i++)
    {
        result[resultSize] = setElements[index1][i];
        resultSize++;
    }
    
    for(int i = 0; i < setElementCounts[index2]; i++)
    {
        bool found = false;
        for(int j = 0; j < resultSize; j++)
        {
            if(result[j] == setElements[index2][i])
            {
                found = true;
                break;
            }
        }
        if(!found)
        {
            result[resultSize] = setElements[index2][i];
            resultSize++;
        }
    }
}

void SetOperations::intersectionSets(string set1, string set2, string result[], int& resultSize) 
{
    int index1 = findSet(set1);
    int index2 = findSet(set2);
    resultSize = 0;
    
    if(index1 == -1 || index2 == -1)
    {
        return;
    }
    
    for(int i = 0; i < setElementCounts[index1]; i++)
    {
        for(int j = 0; j < setElementCounts[index2]; j++)
        {
            if(setElements[index1][i] == setElements[index2][j])
            {
                result[resultSize] = setElements[index1][i];
                resultSize++;
                break;
            }
        }
    }
}

void SetOperations::differenceSets(string set1, string set2, string result[], int& resultSize) 
{
    int index1 = findSet(set1);
    int index2 = findSet(set2);
    resultSize = 0;
    
    if(index1 == -1 || index2 == -1)
    {
        return;
    }
    
    for(int i = 0; i < setElementCounts[index1]; i++)
    {
        bool found = false;
        for(int j = 0; j < setElementCounts[index2]; j++)
        {
            if(setElements[index1][i] == setElements[index2][j])
            {
                found = true;
                break;
            }
        }
        if(!found)
        {
            result[resultSize] = setElements[index1][i];
            resultSize++;
        }
    }
}

void SetOperations::powerSet(string setName, string result[][MAX_SIZE], int resultSizes[], int& resultCount) 
{
    int index = findSet(setName);
    if(index == -1)
    {
        resultCount = 0;
        return;
    }
    
    int n = setElementCounts[index];
    int powerSetSize = (int)pow(2, n);
    resultCount = 0;
    
    for(int i = 0; i < powerSetSize; i++)
    {
        resultSizes[resultCount] = 0;
        for(int j = 0; j < n; j++)
        {
            if(i & (1 << j))
            {
                result[resultCount][resultSizes[resultCount]] = setElements[index][j];
                resultSizes[resultCount]++;
            }
        }
        resultCount++;
    }
}

bool SetOperations::isSubset(string set1, string set2) 
{
    int index1 = findSet(set1);
    int index2 = findSet(set2);
    
    if(index1 == -1 || index2 == -1)
    {
        return false;
    }
    
    for(int i = 0; i < setElementCounts[index1]; i++)
    {
        bool found = false;
        for(int j = 0; j < setElementCounts[index2]; j++)
        {
            if(setElements[index1][i] == setElements[index2][j])
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

void SetOperations::displaySet(string setName) 
{
    int index = findSet(setName);
    if(index == -1)
    {
        cout << "Set not found!" << endl;
        return;
    }
    
    cout << setName << " = { ";
    for(int i = 0; i < setElementCounts[index]; i++)
    {
        cout << setElements[index][i] << " ";
    }
    cout << "}" << endl;
}

// ============= RELATIONS MANAGER IMPLEMENTATION =============
RelationsManager::RelationsManager() 
{
    relationCount = 0;
}

int RelationsManager::findRelation(string name) 
{
    for(int i = 0; i < relationCount; i++)
    {
        if(relations[i].name == name)
        {
            return i;
        }
    }
    return -1;
}

void RelationsManager::addRelation(string name, string pairs[][2], int pairCount) 
{
    relations[relationCount].name = name;
    relations[relationCount].pairCount = pairCount;
    for(int i = 0; i < pairCount; i++)
    {
        relations[relationCount].pairs[i][0] = pairs[i][0];
        relations[relationCount].pairs[i][1] = pairs[i][1];
    }
    relationCount++;
}

bool RelationsManager::isReflexive(string relationName, string elements[], int elementCount) 
{
    int index = findRelation(relationName);
    if(index == -1)
    {
        return false;
    }
    
    for(int i = 0; i < elementCount; i++)
    {
        bool found = false;
        for(int j = 0; j < relations[index].pairCount; j++)
        {
            if(relations[index].pairs[j][0] == elements[i] && 
               relations[index].pairs[j][1] == elements[i])
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

bool RelationsManager::isSymmetric(string relationName) 
{
    int index = findRelation(relationName);
    if(index == -1)
    {
        return false;
    }
    
    for(int i = 0; i < relations[index].pairCount; i++)
    {
        bool found = false;
        for(int j = 0; j < relations[index].pairCount; j++)
        {
            if(relations[index].pairs[j][0] == relations[index].pairs[i][1] && 
               relations[index].pairs[j][1] == relations[index].pairs[i][0])
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

bool RelationsManager::isTransitive(string relationName) 
{
    int index = findRelation(relationName);
    if(index == -1)
    {
        return false;
    }
    
    for(int i = 0; i < relations[index].pairCount; i++)
    {
        for(int j = 0; j < relations[index].pairCount; j++)
        {
            if(relations[index].pairs[i][1] == relations[index].pairs[j][0])
            {
                bool found = false;
                for(int k = 0; k < relations[index].pairCount; k++)
                {
                    if(relations[index].pairs[k][0] == relations[index].pairs[i][0] && 
                       relations[index].pairs[k][1] == relations[index].pairs[j][1])
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
        }
    }
    return true;
}

bool RelationsManager::isEquivalence(string relationName, string elements[], int elementCount) 
{
    return isReflexive(relationName, elements, elementCount) && 
           isSymmetric(relationName) && 
           isTransitive(relationName);
}

void RelationsManager::composeRelations(string rel1, string rel2, string result[][2], int& resultCount) 
{
    int index1 = findRelation(rel1);
    int index2 = findRelation(rel2);
    resultCount = 0;
    
    if(index1 == -1 || index2 == -1)
    {
        return;
    }
    
    for(int i = 0; i < relations[index1].pairCount; i++)
    {
        for(int j = 0; j < relations[index2].pairCount; j++)
        {
            if(relations[index1].pairs[i][1] == relations[index2].pairs[j][0])
            {
                result[resultCount][0] = relations[index1].pairs[i][0];
                result[resultCount][1] = relations[index2].pairs[j][1];
                resultCount++;
            }
        }
    }
}

void RelationsManager::displayRelation(string name) 
{
    int index = findRelation(name);
    if(index == -1)
    {
        cout << "Relation not found!" << endl;
        return;
    }
    
    cout << "\nRelation " << name << " = { ";
    for(int i = 0; i < relations[index].pairCount; i++)
    {
        cout << "(" << relations[index].pairs[i][0] << "," 
             << relations[index].pairs[i][1] << ") ";
    }
    cout << "}" << endl;
}

// ============= FUNCTIONS MANAGER IMPLEMENTATION =============
FunctionsManager::FunctionsManager() 
{
    functionCount = 0;
}

int FunctionsManager::findFunction(string name) 
{
    for(int i = 0; i < functionCount; i++)
    {
        if(functions[i].name == name)
        {
            return i;
        }
    }
    return -1;
}

void FunctionsManager::addFunction(string name, string domain[], string codomain[], int size) 
{
    functions[functionCount].name = name;
    functions[functionCount].mappingCount = size;
    for(int i = 0; i < size; i++)
    {
        functions[functionCount].domain[i] = domain[i];
        functions[functionCount].codomain[i] = codomain[i];
    }
    functionCount++;
}

bool FunctionsManager::isInjective(string funcName) 
{
    int index = findFunction(funcName);
    if(index == -1)
    {
        return false;
    }
    
    for(int i = 0; i < functions[index].mappingCount; i++)
    {
        for(int j = i + 1; j < functions[index].mappingCount; j++)
        {
            if(functions[index].codomain[i] == functions[index].codomain[j])
            {
                return false;
            }
        }
    }
    return true;
}

bool FunctionsManager::isSurjective(string funcName, string codomain[], int codomainSize) 
{
    int index = findFunction(funcName);
    if(index == -1)
    {
        return false;
    }
    
    for(int i = 0; i < codomainSize; i++)
    {
        bool found = false;
        for(int j = 0; j < functions[index].mappingCount; j++)
        {
            if(functions[index].codomain[j] == codomain[i])
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

bool FunctionsManager::isBijective(string funcName, string codomain[], int codomainSize) 
{
    return isInjective(funcName) && isSurjective(funcName, codomain, codomainSize);
}

void FunctionsManager::composeFunctions(string func1, string func2, string resultDomain[], 
                                       string resultCodomain[], int& resultSize) 
{
    int index1 = findFunction(func1);
    int index2 = findFunction(func2);
    resultSize = 0;
    
    if(index1 == -1 || index2 == -1)
    {
        return;
    }
    
    for(int i = 0; i < functions[index1].mappingCount; i++)
    {
        for(int j = 0; j < functions[index2].mappingCount; j++)
        {
            if(functions[index1].codomain[i] == functions[index2].domain[j])
            {
                resultDomain[resultSize] = functions[index1].domain[i];
                resultCodomain[resultSize] = functions[index2].codomain[j];
                resultSize++;
            }
        }
    }
}

void FunctionsManager::inverseFunction(string funcName, string resultDomain[], 
                                      string resultCodomain[], int& resultSize) 
{
    int index = findFunction(funcName);
    resultSize = 0;
    
    if(index == -1 || !isInjective(funcName))
    {
        return;
    }
    
    for(int i = 0; i < functions[index].mappingCount; i++)
    {
        resultDomain[resultSize] = functions[index].codomain[i];
        resultCodomain[resultSize] = functions[index].domain[i];
        resultSize++;
    }
}

void FunctionsManager::displayFunction(string name) 
{
    int index = findFunction(name);
    if(index == -1)
    {
        cout << "Function not found!" << endl;
        return;
    }
    
    cout << "\nFunction " << name << ":" << endl;
    for(int i = 0; i < functions[index].mappingCount; i++)
    {
        cout << "  " << functions[index].domain[i] << " -> " 
             << functions[index].codomain[i] << endl;
    }
}

// ============= PROOF VERIFIER IMPLEMENTATION =============
ProofVerifier::ProofVerifier() 
{
    stepCount = 0;
}

void ProofVerifier::addProofStep(string step) 
{
    proofSteps[stepCount] = step;
    stepCount++;
}

bool ProofVerifier::verifyInductionProof(string baseCase, string inductiveStep) 
{
    cout << "\n=== Verifying Induction Proof ===" << endl;
    cout << "Base Case: " << baseCase << endl;
    cout << "Inductive Step: " << inductiveStep << endl;
    cout << "Proof is valid if both steps are satisfied." << endl;
    return true;
}

bool ProofVerifier::verifyLogicProof(string premises[], int premiseCount, string conclusion) 
{
    cout << "\n=== Verifying Logic Proof ===" << endl;
    cout << "Premises:" << endl;
    for(int i = 0; i < premiseCount; i++)
    {
        cout << "  - " << premises[i] << endl;
    }
    cout << "Conclusion: " << conclusion << endl;
    return true;
}

void ProofVerifier::displayProof() 
{
    cout << "\n=== Proof Steps ===" << endl;
    for(int i = 0; i < stepCount; i++)
    {
        cout << "Step " << (i + 1) << ": " << proofSteps[i] << endl;
    }
}

void ProofVerifier::clearProof() 
{
    stepCount = 0;
}

// ============= CONSISTENCY CHECKER IMPLEMENTATION =============
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

// ============= SUPPORTING CLASSES IMPLEMENTATION =============
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

Room::Room() 
{
    roomNo = "";
    capacity = 0;
    isLab = false;
}

Room::Room(string roomNo, int capacity, bool isLab) 
{
    this->roomNo = roomNo;
    this->capacity = capacity;
    this->isLab = isLab;
}

string Room::getRoomNo() 
{
    return roomNo;
}

int Room::getCapacity() 
{
    return capacity;
}

bool Room::getIsLab() 
{
    return isLab;
}

void Room::display() 
{
    cout << "Room: " << roomNo << ", Capacity: " << capacity 
         << ", Lab: " << (isLab ? "Yes" : "No") << endl;
}