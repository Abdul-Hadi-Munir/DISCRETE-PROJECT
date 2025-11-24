#pragma once

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int MAX_SIZE = 100;
const int MAX_STUDENTS = 50;
const int MAX_COURSES = 50;
const int MAX_FACULTY = 30;
const int MAX_ROOMS = 20;
const int MAX_SEQUENCES = 1000;
const int MAX_GROUPS = 1000;
const int MAX_PREREQS = 10;
const int MAX_RULES = 50;
const int MAX_SETS = 20;
const int MAX_RELATIONS = 20;
const int MAX_FUNCTIONS = 20;
const int MAX_PROOF_STEPS = 50;
const int MAX_CONFLICTS = 50;

// Forward declarations
class Student;
class Course;
class Faculty;
class Room;

// ============= 1. COURSE PERMUTATION & SCHEDULING =============
class CourseScheduler 
{
private:
    string courseNames[MAX_COURSES];
    string prereqList[MAX_COURSES][MAX_PREREQS];
    int prereqCount[MAX_COURSES];
    int courseCount;
    
    string sequences[MAX_SEQUENCES][MAX_COURSES];
    int sequenceLengths[MAX_SEQUENCES];
    int sequenceCount;
    
    void generateSequencesHelper(string current[], int currentSize, 
                                 bool completed[], string remaining[], int remainingSize);
    
public:
    CourseScheduler();
    void addPrerequisite(string course, string prereq);
    void generateAllValidSequences(string courses[], int size);
    void displaySequences();
};

// ============= 2. STUDENT GROUP COMBINATION =============
class GroupManager 
{
private:
    Student* students[MAX_STUDENTS];
    int studentCount;
    
    Student* groups[MAX_GROUPS][MAX_STUDENTS];
    int groupSizes[MAX_GROUPS];
    int groupCount;
    
    void generateCombinationsHelper(int start, int groupSize, 
                                   Student* current[], int currentSize);
    
public:
    GroupManager();
    void addStudent(Student* s);
    void generateGroups(int groupSize);
    void displayGroups();
    int calculateCombinations(int n, int r);
};

// ============= 3. INDUCTION & STRONG INDUCTION =============
class InductionVerifier 
{
private:
    string courses[MAX_COURSES];
    string prereqChains[MAX_COURSES][MAX_PREREQS];
    int chainLengths[MAX_COURSES];
    int courseCount;
    
    bool verifyBaseCase(string course);
    bool verifyInductiveStep(string course, string completed[], int completedSize);
    
public:
    InductionVerifier();
    void addPrerequisiteChain(string course, string prereqs[], int size);
    bool verifyPrerequisites(string targetCourse, string completedCourses[], int size);
    void displayChain(string course);
};

// ============= 4. LOGIC & INFERENCE ENGINE =============
class LogicEngine 
{
private:
    struct Rule 
    {
        string condition;
        string conclusion;
        string type;
    };
    
    Rule rules[MAX_RULES];
    int ruleCount;
    
    string factNames[MAX_SIZE];
    bool factValues[MAX_SIZE];
    int factCount;
    
    int findFact(string fact);
    
public:
    LogicEngine();
    void addRule(string condition, string conclusion, string type);
    void addFact(string fact, bool value);
    bool evaluate(string query);
    void performInference();
    void displayRules();
};

// ============= 5. SET OPERATIONS MODULE =============
class SetOperations 
{
private:
    string setNames[MAX_SETS];
    string setElements[MAX_SETS][MAX_SIZE];
    int setElementCounts[MAX_SETS];
    int setCount;
    
    int findSet(string name);
    
public:
    SetOperations();
    void createSet(string name, string elements[], int size);
    void unionSets(string set1, string set2, string result[], int& resultSize);
    void intersectionSets(string set1, string set2, string result[], int& resultSize);
    void differenceSets(string set1, string set2, string result[], int& resultSize);
    void powerSet(string setName, string result[][MAX_SIZE], int resultSizes[], int& resultCount);
    bool isSubset(string set1, string set2);
    void displaySet(string setName);
};

// ============= 6. RELATIONS MODULE =============
class RelationsManager 
{
private:
    struct Relation 
    {
        string name;
        string pairs[MAX_SIZE][2];
        int pairCount;
    };
    
    Relation relations[MAX_RELATIONS];
    int relationCount;
    
    int findRelation(string name);
    
public:
    RelationsManager();
    void addRelation(string name, string pairs[][2], int pairCount);
    bool isReflexive(string relationName, string elements[], int elementCount);
    bool isSymmetric(string relationName);
    bool isTransitive(string relationName);
    bool isEquivalence(string relationName, string elements[], int elementCount);
    void composeRelations(string rel1, string rel2, string result[][2], int& resultCount);
    void displayRelation(string name);
};

// ============= 7. FUNCTIONS MODULE =============
class FunctionsManager 
{
private:
    struct Function 
    {
        string name;
        string domain[MAX_SIZE];
        string codomain[MAX_SIZE];
        int mappingCount;
    };
    
    Function functions[MAX_FUNCTIONS];
    int functionCount;
    
    int findFunction(string name);
    
public:
    FunctionsManager();
    void addFunction(string name, string domain[], string codomain[], int size);
    bool isInjective(string funcName);
    bool isSurjective(string funcName, string codomain[], int codomainSize);
    bool isBijective(string funcName, string codomain[], int codomainSize);
    void composeFunctions(string func1, string func2, string resultDomain[], 
                         string resultCodomain[], int& resultSize);
    void inverseFunction(string funcName, string resultDomain[], 
                        string resultCodomain[], int& resultSize);
    void displayFunction(string name);
};

// ============= 8. AUTOMATED PROOF & VERIFICATION =============
class ProofVerifier 
{
private:
    string proofSteps[MAX_PROOF_STEPS];
    int stepCount;
    
public:
    ProofVerifier();
    void addProofStep(string step);
    bool verifyInductionProof(string baseCase, string inductiveStep);
    bool verifyLogicProof(string premises[], int premiseCount, string conclusion);
    void displayProof();
    void clearProof();
};

// ============= 9. CONSISTENCY CHECKER =============
class ConsistencyChecker 
{
private:
    string conflicts[MAX_CONFLICTS];
    int conflictCount;
    
public:
    ConsistencyChecker();
    bool checkStudentOverload(string student, int maxCourses, int courseCount);
    void displayConflicts();
    void clearConflicts();
};

// ============= SUPPORTING CLASSES =============
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

class Course 
{
private:
    string code;
    string name;
    string prerequisites[MAX_PREREQS];
    int prereqCount;
    int credits;
    
public:
    Course();
    Course(string code, string name, int credits);
    void addPrerequisite(string prereq);
    
    string getCode();
    string getName();
    void getPrerequisites(string prereqs[], int& count);
    
    void display();
};

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

class Room 
{
private:
    string roomNo;
    int capacity;
    bool isLab;
    
public:
    Room();
    Room(string roomNo, int capacity, bool isLab);
    
    string getRoomNo();
    int getCapacity();
    bool getIsLab();
    
    void display();
};