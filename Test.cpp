#include <iostream>
#include <string>
#include "HeaderFiles/Constants.h"
#include "HeaderFiles/Student.h"
#include "HeaderFiles/Course.h"
#include "HeaderFiles/Faculty.h"
#include "HeaderFiles/CourseScheduler.h"
#include "HeaderFiles/GroupManager.h"
#include "HeaderFiles/InductionVerifier.h"
#include "HeaderFiles/LogicEngine.h"
#include "HeaderFiles/SetOperations.h"
#include "HeaderFiles/RelationsManager.h"
#include "HeaderFiles/FunctionsManager.h"
#include "HeaderFiles/ProofVerifier.h"
#include "HeaderFiles/ConsistencyChecker.h"

using namespace std;

// instances
CourseScheduler scheduler;
GroupManager groupManager;
InductionVerifier inductionVerifier;
LogicEngine logicEngine;
SetOperations setOps;
RelationsManager relationsManager;
FunctionsManager functionsManager;
ProofVerifier proofVerifier;
ConsistencyChecker consistencyChecker;

void printHeader(string title)
{
    cout << " TESTING: " << title << endl;
}

void testStudentCourseEnrollment()
{
    printHeader("STUDENT & COURSE MANAGEMENT");

    // 1. Create Students
    Student s1("S001", "A.Hadi");
    Student s2("S002", "M.Saim");
    Student s3("S003", "Musab");
    Student s4("S004", "Abdullah");
    Student s5("S005", "Areeba");

    cout << "Created Students: A.Hadi, M.Saim, Musab, Abdullah, Areeba" << endl;

    // 2. Create Courses
    Course c1("CS101", "Discrete Structures", 3);
    Course c2("CS102", "Data Structures", 3);
    Course c3("CS103", "Algorithms", 3);

    // 3. Define Prerequisites
    c2.addPrerequisite("CS101");
    c3.addPrerequisite("CS102");

    scheduler.addPrerequisite("CS102", "CS101");
    scheduler.addPrerequisite("CS103", "CS102");

    cout << "Created Courses: CS101 -> CS102 -> CS103" << endl;

    // 4. Enroll and Complete
    cout << "\n[Action] Enroll M.Saim in CS101..." << endl;
    s2.enrollCourse("CS101");

    cout << "[Action] M.Saim completes CS101..." << endl;
    s2.completeCourse("CS101");

    cout << "[Action] Enroll M.Saim in CS102 (Prereq satisfied)..." << endl;
    s2.enrollCourse("CS102");

    cout << "\n--- Student Status: M.Saim ---" << endl;
    s2.display();
}

void testGroups()
{
    printHeader("GROUP COMBINATIONS (Combinatorics)");

    groupManager.addStudent(new Student("S001", "A.Hadi"));
    groupManager.addStudent(new Student("S002", "M.Saim"));
    groupManager.addStudent(new Student("S003", "Musab"));
    groupManager.addStudent(new Student("S004", "Abdullah"));
    groupManager.addStudent(new Student("S005", "Areeba"));
    groupManager.addStudent(new Student("S006", "Aerum"));
    groupManager.addStudent(new Student("S007", "Hanniya"));

    cout << "Pool: A.Hadi, M.Saim, Musab, Abdullah, Areeba, Aerum, Hanniya" << endl;
    cout << "Calculating combinations for groups of size 3..." << endl;

    int total = groupManager.calculateCombinations(7, 3);
    cout << "Total possible groups (7C3): " << total << endl;

    groupManager.generateGroups(3);
    groupManager.displayGroups();
}

void testSets()
{
    printHeader("SET OPERATIONS");

    string setA[] = {"Areeba", "Aerum", "Hanniya", "M.Saim"};
    string setB[] = {"M.Saim", "Abdullah", "Musab", "Areeba"};

    setOps.createSet("Girls+Saim", setA, 4);
    setOps.createSet("Boys+Areeba", setB, 4);

    cout << "Set A: {Areeba, Aerum, Hanniya, M.Saim}" << endl;
    cout << "Set B: {M.Saim, Abdullah, Musab, Areeba}" << endl;

    string result[MAX_SIZE];
    int size;

    // Union
    setOps.unionSets("Girls+Saim", "Boys+Areeba", result, size);
    cout << "\nUnion (A U B): { ";
    for (int i = 0; i < size; i++)
    {
        cout << result[i];
        if (i < size - 1)
        {
            cout << ", ";
        }
    }
    cout << " }" << endl;

    // Intersection
    setOps.intersectionSets("Girls+Saim", "Boys+Areeba", result, size);
    cout << "Intersection (A n B): { ";
    for (int i = 0; i < size; i++)
    {
        cout << result[i];
        if (i < size - 1)
        {
            cout << ", ";
        }
    }
    cout << " }" << endl;
}

void testRelations()
{
    printHeader("RELATIONS PROPERTIES");

    string elements[] = {"M.Saim", "Musab", "Abdullah"};

    string pairs[MAX_SIZE][2] =
    {
        {"M.Saim", "M.Saim"},
        {"Musab", "Musab"},
        {"Abdullah", "Abdullah"},
        {"M.Saim", "Musab"}, {"Musab", "M.Saim"},
        {"Musab", "Abdullah"}, {"Abdullah", "Musab"},
        {"M.Saim", "Abdullah"}, {"Abdullah", "M.Saim"}
    };

    relationsManager.addRelation("Friendship", pairs, 9);
    relationsManager.displayRelation("Friendship");

    cout << "\nChecking Properties:" << endl;
    cout << "Reflexive?  " << (relationsManager.isReflexive("Friendship", elements, 3) ? "YES" : "NO") << endl;
    cout << "Symmetric?  " << (relationsManager.isSymmetric("Friendship") ? "YES" : "NO") << endl;
    cout << "Transitive? " << (relationsManager.isTransitive("Friendship") ? "YES" : "NO") << endl;
    cout << "Equivalence?" << (relationsManager.isEquivalence("Friendship", elements, 3) ? "YES" : "NO") << endl;
}

void testLogicEngine()
{
    printHeader("LOGIC ENGINE (Inference)");

    logicEngine.addRule("A.Hadi_Studies", "A.Hadi_Gets_A", "Implication");
    logicEngine.addFact("A.Hadi_Studies", true);

    cout << "Rule: If A.Hadi_Studies -> A.Hadi_Gets_A" << endl;
    cout << "Fact: A.Hadi_Studies is TRUE" << endl;
    cout << "Fact: A.Hadi_Gets_A is currently UNKNOWN" << endl;

    logicEngine.performInference();

    bool result = logicEngine.evaluate("A.Hadi_Gets_A");
    cout << "Result after inference: A.Hadi_Gets_A is "
         << (result ? "TRUE" : "FALSE") << endl;
}

void testProofVerifier()
{
    printHeader("MATHEMATICAL INDUCTION PROOF");

    string base = "Base Case P(1): For n=1, 1 = 1(1+1)/2. 1 = 1. TRUE.";
    string step = "Inductive Step: Assume P(k) is true. Show P(k+1) is true.";

    proofVerifier.verifyInductionProof(base, step);
}

void testFunctions()
{
    printHeader("FUNCTIONS (Mapping)");

    string domain[] = {"A.Hadi", "M.Saim", "Musab"};
    string codomain[] = {"Room101", "Room102", "Room103"};

    string mapDomain[] = {"A.Hadi", "M.Saim", "Musab"};
    string mapCodomain[] = {"Room101", "Room102", "Room103"};

    functionsManager.addFunction("RoomAssignment", mapDomain, mapCodomain, 3);
    functionsManager.displayFunction("RoomAssignment");

    cout << "Is Injective (One-to-One)? " << (functionsManager.isInjective("RoomAssignment") ? "YES" : "NO") << endl;
    cout << "Is Surjective (Onto)?      " << (functionsManager.isSurjective("RoomAssignment", codomain, 3) ? "YES" : "NO") << endl;
}

int main()
{
    cout << "RUNNING HARDCORE TESTS..." << endl;

    testStudentCourseEnrollment();
    testGroups();
    testSets();
    testRelations();
    testLogicEngine();
    testProofVerifier();
    testFunctions();

    cout << "\n\nALL TESTS COMPLETED." << endl;

    return 0;
}
