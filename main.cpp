#include "Discretemath.cpp"

// Global Data Storage
Student studentList[MAX_STUDENTS];
int totalStudents = 0;

Course courseList[MAX_COURSES];
int totalCourses = 0;

Faculty facultyList[MAX_FACULTY];
int totalFaculty = 0;

Room roomList[MAX_ROOMS];
int totalRooms = 0;

// Module Instances
CourseScheduler scheduler;
GroupManager groupManager;
InductionVerifier inductionVerifier;
LogicEngine logicEngine;
SetOperations setOps;
RelationsManager relationsManager;
FunctionsManager functionsManager;
ProofVerifier proofVerifier;
ConsistencyChecker consistencyChecker;

// Utility Functions
void clearScreen()
{
    cout << "\n\n";
}

void pauseScreen()
{
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

int getValidChoice(int min, int max)
{
    int choice;
    while (true)
    {
        cout << "Enter choice: ";
        if (cin >> choice && choice >= min && choice <= max)
            return choice;
        cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

string getStringInput(string prompt)
{
    string input;
    cout << prompt;
    cin >> input;
    return input;
}

int getIntInput(string prompt)
{
    int input;
    while (true)
    {
        cout << prompt;
        if (cin >> input)
            return input;
        cout << "Invalid input. Please enter a number.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

// ==================== STUDENT MANAGEMENT ====================
void addStudent()
{
    if (totalStudents >= MAX_STUDENTS)
    {
        cout << "Maximum student limit reached." << endl;
        return;
    }

    string id = getStringInput("Enter Student ID: ");
    string name = getStringInput("Enter Student Name: ");

    studentList[totalStudents] = Student(id, name);
    groupManager.addStudent(&studentList[totalStudents]);
    totalStudents++;

    cout << "\nStudent added successfully!" << endl;
}

void viewAllStudents()
{
    if (totalStudents == 0)
    {
        cout << "\nNo students registered." << endl;
        return;
    }

    cout << "\n========== All Students ==========" << endl;
    for (int i = 0; i < totalStudents; i++)
    {
        cout << (i + 1) << ". " << studentList[i].getId() << " - " << studentList[i].getName() << endl;
    }
}

void enrollStudentInCourse()
{
    if (totalStudents == 0 || totalCourses == 0)
    {
        cout << "\nNeed at least one student and one course." << endl;
        return;
    }

    viewAllStudents();
    int sIdx = getIntInput("\nSelect student number: ") - 1;
    
    if (sIdx < 0 || sIdx >= totalStudents)
    {
        cout << "Invalid selection." << endl;
        return;
    }

    cout << "\nAvailable Courses:" << endl;
    for (int i = 0; i < totalCourses; i++)
        cout << (i + 1) << ". " << courseList[i].getCode() << " - " << courseList[i].getName() << endl;

    int cIdx = getIntInput("Select course number: ") - 1;
    
    if (cIdx < 0 || cIdx >= totalCourses)
    {
        cout << "Invalid selection." << endl;
        return;
    }

    studentList[sIdx].enrollCourse(courseList[cIdx].getCode());
    cout << "\nStudent enrolled successfully!" << endl;
}

void markCourseComplete()
{
    if (totalStudents == 0)
    {
        cout << "\nNo students registered." << endl;
        return;
    }

    viewAllStudents();
    int sIdx = getIntInput("\nSelect student number: ") - 1;
    
    if (sIdx < 0 || sIdx >= totalStudents)
    {
        cout << "Invalid selection." << endl;
        return;
    }

    string enrolled[MAX_COURSES];
    int count;
    studentList[sIdx].getEnrolledCourses(enrolled, count);

    if (count == 0)
    {
        cout << "\nStudent has no enrolled courses." << endl;
        return;
    }

    cout << "\nEnrolled Courses:" << endl;
    for (int i = 0; i < count; i++)
        cout << (i + 1) << ". " << enrolled[i] << endl;

    int cIdx = getIntInput("Select course to mark complete: ") - 1;
    
    if (cIdx < 0 || cIdx >= count)
    {
        cout << "Invalid selection." << endl;
        return;
    }

    studentList[sIdx].completeCourse(enrolled[cIdx]);
    cout << "\nCourse marked as complete!" << endl;
}

void viewStudentDetails()
{
    if (totalStudents == 0)
    {
        cout << "\nNo students registered." << endl;
        return;
    }

    viewAllStudents();
    int idx = getIntInput("\nSelect student number: ") - 1;
    
    if (idx < 0 || idx >= totalStudents)
    {
        cout << "Invalid selection." << endl;
        return;
    }

    studentList[idx].display();
}

void studentManagementMenu()
{
    int choice;
    do
    {
        clearScreen();
        cout << "========== Student Management ==========" << endl;
        cout << "1. Add New Student" << endl;
        cout << "2. View All Students" << endl;
        cout << "3. Enroll Student in Course" << endl;
        cout << "4. Mark Course Complete" << endl;
        cout << "5. View Student Details" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "========================================" << endl;

        choice = getValidChoice(0, 5);

        switch (choice)
        {
            case 1: addStudent(); break;
            case 2: viewAllStudents(); break;
            case 3: enrollStudentInCourse(); break;
            case 4: markCourseComplete(); break;
            case 5: viewStudentDetails(); break;
        }

        if (choice != 0) pauseScreen();
    } while (choice != 0);
}

// ==================== COURSE MANAGEMENT ====================
void addCourse()
{
    if (totalCourses >= MAX_COURSES)
    {
        cout << "Maximum course limit reached." << endl;
        return;
    }

    string code = getStringInput("Enter Course Code: ");
    string name = getStringInput("Enter Course Name: ");
    int credits = getIntInput("Enter Credits: ");

    courseList[totalCourses] = Course(code, name, credits);

    int numPrereqs = getIntInput("Number of prerequisites (0 if none): ");
    for (int i = 0; i < numPrereqs; i++)
    {
        string prereq = getStringInput("Enter prerequisite " + to_string(i + 1) + " code: ");
        courseList[totalCourses].addPrerequisite(prereq);
        scheduler.addPrerequisite(code, prereq);
    }

    totalCourses++;
    cout << "\nCourse added successfully!" << endl;
}

void viewAllCourses()
{
    if (totalCourses == 0)
    {
        cout << "\nNo courses registered." << endl;
        return;
    }

    cout << "\n========== All Courses ==========" << endl;
    for (int i = 0; i < totalCourses; i++)
    {
        cout << (i + 1) << ". " << courseList[i].getCode() << " - " 
             << courseList[i].getName() << " (" << courseList[i].getCode() << ")" << endl;
    }
}

void viewCourseDetails()
{
    if (totalCourses == 0)
    {
        cout << "\nNo courses registered." << endl;
        return;
    }

    viewAllCourses();
    int idx = getIntInput("\nSelect course number: ") - 1;
    
    if (idx < 0 || idx >= totalCourses)
    {
        cout << "Invalid selection." << endl;
        return;
    }

    courseList[idx].display();
}

void generateCourseSequences()
{
    if (totalCourses == 0)
    {
        cout << "\nNo courses available." << endl;
        return;
    }

    cout << "\nSelect courses for sequence generation:" << endl;
    viewAllCourses();

    int n = getIntInput("\nHow many courses to include? ");
    if (n <= 0 || n > totalCourses)
    {
        cout << "Invalid number." << endl;
        return;
    }

    string selected[MAX_COURSES];
    for (int i = 0; i < n; i++)
    {
        int idx = getIntInput("Select course " + to_string(i + 1) + ": ") - 1;
        if (idx >= 0 && idx < totalCourses)
            selected[i] = courseList[idx].getCode();
    }

    scheduler.generateAllValidSequences(selected, n);
    scheduler.displaySequences();
}

void addPrerequisiteChain()
{
    if (totalCourses == 0)
    {
        cout << "\nNo courses available." << endl;
        return;
    }

    viewAllCourses();
    int idx = getIntInput("\nSelect course to add prerequisite chain: ") - 1;
    
    if (idx < 0 || idx >= totalCourses)
    {
        cout << "Invalid selection." << endl;
        return;
    }

    int n = getIntInput("Number of prerequisites in chain: ");
    string prereqs[MAX_PREREQS];
    
    for (int i = 0; i < n && i < MAX_PREREQS; i++)
        prereqs[i] = getStringInput("Prerequisite " + to_string(i + 1) + ": ");

    inductionVerifier.addPrerequisiteChain(courseList[idx].getCode(), prereqs, n);
    cout << "\nPrerequisite chain added!" << endl;
}

void verifyPrerequisites()
{
    if (totalStudents == 0 || totalCourses == 0)
    {
        cout << "\nNeed at least one student and one course." << endl;
        return;
    }

    viewAllStudents();
    int sIdx = getIntInput("\nSelect student: ") - 1;
    
    if (sIdx < 0 || sIdx >= totalStudents)
    {
        cout << "Invalid selection." << endl;
        return;
    }

    viewAllCourses();
    int cIdx = getIntInput("Select target course: ") - 1;
    
    if (cIdx < 0 || cIdx >= totalCourses)
    {
        cout << "Invalid selection." << endl;
        return;
    }

    string completed[MAX_COURSES];
    int count;
    studentList[sIdx].getCompletedCourses(completed, count);

    inductionVerifier.verifyPrerequisites(courseList[cIdx].getCode(), completed, count);
}

void courseManagementMenu()
{
    int choice;
    do
    {
        clearScreen();
        cout << "========== Course Management ==========" << endl;
        cout << "1. Add New Course" << endl;
        cout << "2. View All Courses" << endl;
        cout << "3. View Course Details" << endl;
        cout << "4. Generate Valid Course Sequences" << endl;
        cout << "5. Add Prerequisite Chain" << endl;
        cout << "6. Verify Prerequisites for Student" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "=======================================" << endl;

        choice = getValidChoice(0, 6);

        switch (choice)
        {
            case 1: addCourse(); break;
            case 2: viewAllCourses(); break;
            case 3: viewCourseDetails(); break;
            case 4: generateCourseSequences(); break;
            case 5: addPrerequisiteChain(); break;
            case 6: verifyPrerequisites(); break;
        }

        if (choice != 0) pauseScreen();
    } while (choice != 0);
}

// ==================== FACULTY MANAGEMENT ====================
void addFaculty()
{
    if (totalFaculty >= MAX_FACULTY)
    {
        cout << "Maximum faculty limit reached." << endl;
        return;
    }

    string id = getStringInput("Enter Faculty ID: ");
    string name = getStringInput("Enter Faculty Name: ");

    facultyList[totalFaculty++] = Faculty(id, name);
    cout << "\nFaculty added successfully!" << endl;
}

void viewAllFaculty()
{
    if (totalFaculty == 0)
    {
        cout << "\nNo faculty registered." << endl;
        return;
    }

    cout << "\n========== All Faculty ==========" << endl;
    for (int i = 0; i < totalFaculty; i++)
        cout << (i + 1) << ". " << facultyList[i].getId() << " - " << facultyList[i].getName() << endl;
}

void assignCourseToFaculty()
{
    if (totalFaculty == 0 || totalCourses == 0)
    {
        cout << "\nNeed at least one faculty and one course." << endl;
        return;
    }

    viewAllFaculty();
    int fIdx = getIntInput("\nSelect faculty number: ") - 1;
    
    if (fIdx < 0 || fIdx >= totalFaculty)
    {
        cout << "Invalid selection." << endl;
        return;
    }

    viewAllCourses();
    int cIdx = getIntInput("Select course number: ") - 1;
    
    if (cIdx < 0 || cIdx >= totalCourses)
    {
        cout << "Invalid selection." << endl;
        return;
    }

    facultyList[fIdx].assignCourse(courseList[cIdx].getCode());
    cout << "\nCourse assigned successfully!" << endl;
}

void viewFacultyDetails()
{
    if (totalFaculty == 0)
    {
        cout << "\nNo faculty registered." << endl;
        return;
    }

    viewAllFaculty();
    int idx = getIntInput("\nSelect faculty number: ") - 1;
    
    if (idx < 0 || idx >= totalFaculty)
    {
        cout << "Invalid selection." << endl;
        return;
    }

    facultyList[idx].display();
}

void facultyManagementMenu()
{
    int choice;
    do
    {
        clearScreen();
        cout << "========== Faculty Management ==========" << endl;
        cout << "1. Add New Faculty" << endl;
        cout << "2. View All Faculty" << endl;
        cout << "3. Assign Course to Faculty" << endl;
        cout << "4. View Faculty Details" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "========================================" << endl;

        choice = getValidChoice(0, 4);

        switch (choice)
        {
            case 1: addFaculty(); break;
            case 2: viewAllFaculty(); break;
            case 3: assignCourseToFaculty(); break;
            case 4: viewFacultyDetails(); break;
        }

        if (choice != 0) pauseScreen();
    } while (choice != 0);
}

// ==================== ROOM MANAGEMENT ====================
void addRoom()
{
    if (totalRooms >= MAX_ROOMS)
    {
        cout << "Maximum room limit reached." << endl;
        return;
    }

    string roomNo = getStringInput("Enter Room Number: ");
    int capacity = getIntInput("Enter Capacity: ");
    
    cout << "Is this a lab? (1 = Yes, 0 = No): ";
    int isLab = getValidChoice(0, 1);

    roomList[totalRooms++] = Room(roomNo, capacity, isLab == 1);
    cout << "\nRoom added successfully!" << endl;
}

void viewAllRooms()
{
    if (totalRooms == 0)
    {
        cout << "\nNo rooms registered." << endl;
        return;
    }

    cout << "\n========== All Rooms ==========" << endl;
    for (int i = 0; i < totalRooms; i++)
    {
        cout << (i + 1) << ". " << roomList[i].getRoomNo() 
             << " (Capacity: " << roomList[i].getCapacity() 
             << ", " << (roomList[i].getIsLab() ? "Lab" : "Classroom") << ")" << endl;
    }
}

void viewRoomDetails()
{
    if (totalRooms == 0)
    {
        cout << "\nNo rooms registered." << endl;
        return;
    }

    viewAllRooms();
    int idx = getIntInput("\nSelect room number: ") - 1;
    
    if (idx < 0 || idx >= totalRooms)
    {
        cout << "Invalid selection." << endl;
        return;
    }

    roomList[idx].display();
}

void roomManagementMenu()
{
    int choice;
    do
    {
        clearScreen();
        cout << "========== Room Management ==========" << endl;
        cout << "1. Add New Room" << endl;
        cout << "2. View All Rooms" << endl;
        cout << "3. View Room Details" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "=====================================" << endl;

        choice = getValidChoice(0, 3);

        switch (choice)
        {
            case 1: addRoom(); break;
            case 2: viewAllRooms(); break;
            case 3: viewRoomDetails(); break;
        }

        if (choice != 0) pauseScreen();
    } while (choice != 0);
}

// ==================== GROUP MANAGEMENT ====================
void generateStudentGroups()
{
    if (totalStudents < 2)
    {
        cout << "\nNeed at least 2 students to form groups." << endl;
        return;
    }

    cout << "Total students: " << totalStudents << endl;
    int groupSize = getIntInput("Enter group size: ");

    if (groupSize <= 0 || groupSize > totalStudents)
    {
        cout << "Invalid group size." << endl;
        return;
    }

    int totalGroups = groupManager.calculateCombinations(totalStudents, groupSize);
    cout << "\nPossible combinations: C(" << totalStudents << "," << groupSize << ") = " << totalGroups << endl;

    groupManager.generateGroups(groupSize);
    groupManager.displayGroups();
}

void groupManagementMenu()
{
    int choice;
    do
    {
        clearScreen();
        cout << "========== Group Management ==========" << endl;
        cout << "1. Generate Student Groups" << endl;
        cout << "2. View Current Groups" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "======================================" << endl;

        choice = getValidChoice(0, 2);

        switch (choice)
        {
            case 1: generateStudentGroups(); break;
            case 2: groupManager.displayGroups(); break;
        }

        if (choice != 0) pauseScreen();
    } while (choice != 0);
}

// ==================== SET OPERATIONS ====================
void createNewSet()
{
    string name = getStringInput("Enter set name: ");
    int n = getIntInput("Number of elements: ");

    string elements[MAX_SIZE];
    for (int i = 0; i < n && i < MAX_SIZE; i++)
        elements[i] = getStringInput("Element " + to_string(i + 1) + ": ");

    setOps.createSet(name, elements, n);
    cout << "\nSet created: ";
    setOps.displaySet(name);
}

void performUnion()
{
    string set1 = getStringInput("Enter first set name: ");
    string set2 = getStringInput("Enter second set name: ");

    string result[MAX_SIZE];
    int resultSize;
    setOps.unionSets(set1, set2, result, resultSize);

    cout << "\n" << set1 << " U " << set2 << " = { ";
    for (int i = 0; i < resultSize; i++)
    {
        cout << result[i];
        if (i < resultSize - 1) cout << ", ";
    }
    cout << " }" << endl;
}

void performIntersection()
{
    string set1 = getStringInput("Enter first set name: ");
    string set2 = getStringInput("Enter second set name: ");

    string result[MAX_SIZE];
    int resultSize;
    setOps.intersectionSets(set1, set2, result, resultSize);

    cout << "\n" << set1 << " n " << set2 << " = { ";
    for (int i = 0; i < resultSize; i++)
    {
        cout << result[i];
        if (i < resultSize - 1) cout << ", ";
    }
    cout << " }" << endl;
}

void performDifference()
{
    string set1 = getStringInput("Enter first set name: ");
    string set2 = getStringInput("Enter second set name: ");

    string result[MAX_SIZE];
    int resultSize;
    setOps.differenceSets(set1, set2, result, resultSize);

    cout << "\n" << set1 << " - " << set2 << " = { ";
    for (int i = 0; i < resultSize; i++)
    {
        cout << result[i];
        if (i < resultSize - 1) cout << ", ";
    }
    cout << " }" << endl;
}

void generatePowerSet()
{
    string name = getStringInput("Enter set name: ");

    string result[MAX_GROUPS][MAX_SIZE];
    int resultSizes[MAX_GROUPS];
    int resultCount;

    setOps.powerSet(name, result, resultSizes, resultCount);

    cout << "\nPower Set of " << name << " (2^n = " << resultCount << " subsets):" << endl;
    for (int i = 0; i < resultCount; i++)
    {
        cout << "  { ";
        for (int j = 0; j < resultSizes[i]; j++)
        {
            cout << result[i][j];
            if (j < resultSizes[i] - 1) cout << ", ";
        }
        cout << " }" << endl;
    }
}

void checkSubset()
{
    string set1 = getStringInput("Enter subset name: ");
    string set2 = getStringInput("Enter superset name: ");

    bool result = setOps.isSubset(set1, set2);
    cout << "\n" << set1 << (result ? " IS " : " is NOT ") << "a subset of " << set2 << endl;
}

void setOperationsMenu()
{
    int choice;
    do
    {
        clearScreen();
        cout << "========== Set Operations ==========" << endl;
        cout << "1. Create New Set" << endl;
        cout << "2. Union of Sets" << endl;
        cout << "3. Intersection of Sets" << endl;
        cout << "4. Difference of Sets" << endl;
        cout << "5. Generate Power Set" << endl;
        cout << "6. Check Subset" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "====================================" << endl;

        choice = getValidChoice(0, 6);

        switch (choice)
        {
            case 1: createNewSet(); break;
            case 2: performUnion(); break;
            case 3: performIntersection(); break;
            case 4: performDifference(); break;
            case 5: generatePowerSet(); break;
            case 6: checkSubset(); break;
        }

        if (choice != 0) pauseScreen();
    } while (choice != 0);
}

// ==================== RELATIONS ====================
void createRelation()
{
    string name = getStringInput("Enter relation name: ");
    int n = getIntInput("Number of pairs: ");

    string pairs[MAX_SIZE][2];
    for (int i = 0; i < n && i < MAX_SIZE; i++)
    {
        cout << "Pair " << (i + 1) << ":" << endl;
        pairs[i][0] = getStringInput("  First element: ");
        pairs[i][1] = getStringInput("  Second element: ");
    }

    relationsManager.addRelation(name, pairs, n);
    cout << "\nRelation created!" << endl;
    relationsManager.displayRelation(name);
}

void checkRelationProperties()
{
    string name = getStringInput("Enter relation name: ");
    
    int n = getIntInput("Number of elements in domain: ");
    string elements[MAX_SIZE];
    for (int i = 0; i < n && i < MAX_SIZE; i++)
        elements[i] = getStringInput("Element " + to_string(i + 1) + ": ");

    cout << "\n========== Relation Properties ==========" << endl;
    cout << "Reflexive: " << (relationsManager.isReflexive(name, elements, n) ? "Yes" : "No") << endl;
    cout << "Symmetric: " << (relationsManager.isSymmetric(name) ? "Yes" : "No") << endl;
    cout << "Transitive: " << (relationsManager.isTransitive(name) ? "Yes" : "No") << endl;
    cout << "Equivalence: " << (relationsManager.isEquivalence(name, elements, n) ? "Yes" : "No") << endl;
}

void composeRelations()
{
    string rel1 = getStringInput("Enter first relation name: ");
    string rel2 = getStringInput("Enter second relation name: ");

    string result[MAX_SIZE][2];
    int resultCount;
    relationsManager.composeRelations(rel1, rel2, result, resultCount);

    cout << "\n" << rel1 << " o " << rel2 << " = { ";
    for (int i = 0; i < resultCount; i++)
    {
        cout << "(" << result[i][0] << ", " << result[i][1] << ")";
        if (i < resultCount - 1) cout << ", ";
    }
    cout << " }" << endl;
}

void relationsMenu()
{
    int choice;
    do
    {
        clearScreen();
        cout << "========== Relations ==========" << endl;
        cout << "1. Create New Relation" << endl;
        cout << "2. Check Relation Properties" << endl;
        cout << "3. Compose Relations" << endl;
        cout << "4. Display Relation" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "===============================" << endl;

        choice = getValidChoice(0, 4);

        switch (choice)
        {
            case 1: createRelation(); break;
            case 2: checkRelationProperties(); break;
            case 3: composeRelations(); break;
            case 4: 
            {
                string name = getStringInput("Enter relation name: ");
                relationsManager.displayRelation(name);
                break;
            }
        }

        if (choice != 0) pauseScreen();
    } while (choice != 0);
}

// ==================== FUNCTIONS ====================
void createFunction()
{
    string name = getStringInput("Enter function name: ");
    int n = getIntInput("Number of mappings: ");

    string domain[MAX_SIZE], codomain[MAX_SIZE];
    for (int i = 0; i < n && i < MAX_SIZE; i++)
    {
        cout << "Mapping " << (i + 1) << ":" << endl;
        domain[i] = getStringInput("  Domain element: ");
        codomain[i] = getStringInput("  Maps to: ");
    }

    functionsManager.addFunction(name, domain, codomain, n);
    cout << "\nFunction created!" << endl;
    functionsManager.displayFunction(name);
}

void checkFunctionProperties()
{
    string name = getStringInput("Enter function name: ");
    
    int n = getIntInput("Number of elements in codomain: ");
    string codomain[MAX_SIZE];
    for (int i = 0; i < n && i < MAX_SIZE; i++)
        codomain[i] = getStringInput("Codomain element " + to_string(i + 1) + ": ");

    cout << "\n========== Function Properties ==========" << endl;
    cout << "Injective (One-to-One): " << (functionsManager.isInjective(name) ? "Yes" : "No") << endl;
    cout << "Surjective (Onto): " << (functionsManager.isSurjective(name, codomain, n) ? "Yes" : "No") << endl;
    cout << "Bijective: " << (functionsManager.isBijective(name, codomain, n) ? "Yes" : "No") << endl;
}

void composeFunctions()
{
    string func1 = getStringInput("Enter first function name (f): ");
    string func2 = getStringInput("Enter second function name (g): ");

    string resultDomain[MAX_SIZE], resultCodomain[MAX_SIZE];
    int resultSize;
    functionsManager.composeFunctions(func1, func2, resultDomain, resultCodomain, resultSize);

    cout << "\n(g o f):" << endl;
    for (int i = 0; i < resultSize; i++)
        cout << "  " << resultDomain[i] << " -> " << resultCodomain[i] << endl;
}

void findInverse()
{
    string name = getStringInput("Enter function name: ");

    string resultDomain[MAX_SIZE], resultCodomain[MAX_SIZE];
    int resultSize;
    functionsManager.inverseFunction(name, resultDomain, resultCodomain, resultSize);

    if (resultSize > 0)
    {
        cout << "\nInverse function:" << endl;
        for (int i = 0; i < resultSize; i++)
            cout << "  " << resultDomain[i] << " -> " << resultCodomain[i] << endl;
    }
}

void functionsMenu()
{
    int choice;
    do
    {
        clearScreen();
        cout << "========== Functions ==========" << endl;
        cout << "1. Create New Function" << endl;
        cout << "2. Check Function Properties" << endl;
        cout << "3. Compose Functions" << endl;
        cout << "4. Find Inverse Function" << endl;
        cout << "5. Display Function" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "===============================" << endl;

        choice = getValidChoice(0, 5);

        switch (choice)
        {
            case 1: createFunction(); break;
            case 2: checkFunctionProperties(); break;
            case 3: composeFunctions(); break;
            case 4: findInverse(); break;
            case 5:
            {
                string name = getStringInput("Enter function name: ");
                functionsManager.displayFunction(name);
                break;
            }
        }

        if (choice != 0) pauseScreen();
    } while (choice != 0);
}

// ==================== LOGIC ENGINE ====================
void addLogicRule()
{
    string condition = getStringInput("Enter condition (premise): ");
    string conclusion = getStringInput("Enter conclusion: ");
    string type = getStringInput("Enter rule type (e.g., implication, equivalence): ");

    logicEngine.addRule(condition, conclusion, type);
    cout << "\nRule added: " << condition << " => " << conclusion << endl;
}

void addLogicFact()
{
    string fact = getStringInput("Enter fact name: ");
    cout << "Is it true? (1 = Yes, 0 = No): ";
    int value = getValidChoice(0, 1);

    logicEngine.addFact(fact, value == 1);
    cout << "\nFact added: " << fact << " = " << (value ? "TRUE" : "FALSE") << endl;
}

void evaluateQuery()
{
    string query = getStringInput("Enter query to evaluate: ");
    bool result = logicEngine.evaluate(query);
    cout << "\nResult: " << query << " is " << (result ? "TRUE" : "FALSE") << endl;
}

void logicEngineMenu()
{
    int choice;
    do
    {
        clearScreen();
        cout << "========== Logic Engine ==========" << endl;
        cout << "1. Add Rule" << endl;
        cout << "2. Add Fact" << endl;
        cout << "3. Perform Inference" << endl;
        cout << "4. Evaluate Query" << endl;
        cout << "5. Display All Rules" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "==================================" << endl;

        choice = getValidChoice(0, 5);

        switch (choice)
        {
            case 1: addLogicRule(); break;
            case 2: addLogicFact(); break;
            case 3: logicEngine.performInference(); break;
            case 4: evaluateQuery(); break;
            case 5: logicEngine.displayRules(); break;
        }

        if (choice != 0) pauseScreen();
    } while (choice != 0);
}

// ==================== PROOF VERIFIER ====================
void addProofStep()
{
    string step = getStringInput("Enter proof step: ");
    proofVerifier.addProofStep(step);
    cout << "\nStep added!" << endl;
}

void verifyInduction()
{
    cout << "Enter base case statement: ";
    cin.ignore();
    string baseCase;
    getline(cin, baseCase);

    cout << "Enter inductive step statement: ";
    string inductiveStep;
    getline(cin, inductiveStep);

    proofVerifier.verifyInductionProof(baseCase, inductiveStep);
}

void verifyLogicProof()
{
    int n = getIntInput("Number of premises: ");
    
    cin.ignore();
    string premises[MAX_PROOF_STEPS];
    for (int i = 0; i < n && i < MAX_PROOF_STEPS; i++)
    {
        cout << "Premise " << (i + 1) << ": ";
        getline(cin, premises[i]);
    }

    cout << "Conclusion: ";
    string conclusion;
    getline(cin, conclusion);

    proofVerifier.verifyLogicProof(premises, n, conclusion);
}

void proofVerifierMenu()
{
    int choice;
    do
    {
        clearScreen();
        cout << "========== Proof Verifier ==========" << endl;
        cout << "1. Add Proof Step" << endl;
        cout << "2. Display Proof Steps" << endl;
        cout << "3. Verify Induction Proof" << endl;
        cout << "4. Verify Logic Proof" << endl;
        cout << "5. Clear Proof" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "====================================" << endl;

        choice = getValidChoice(0, 5);

        switch (choice)
        {
            case 1: addProofStep(); break;
            case 2: proofVerifier.displayProof(); break;
            case 3: verifyInduction(); break;
            case 4: verifyLogicProof(); break;
            case 5: 
                proofVerifier.clearProof(); 
                cout << "\nProof cleared!" << endl;
                break;
        }

        if (choice != 0) pauseScreen();
    } while (choice != 0);
}

// ==================== CONSISTENCY CHECKER ====================
void checkStudentLoad()
{
    if (totalStudents == 0)
    {
        cout << "\nNo students registered." << endl;
        return;
    }

    viewAllStudents();
    int idx = getIntInput("\nSelect student: ") - 1;
    
    if (idx < 0 || idx >= totalStudents)
    {
        cout << "Invalid selection." << endl;
        return;
    }

    int maxCourses = getIntInput("Maximum allowed courses: ");

    string enrolled[MAX_COURSES];
    int count;
    studentList[idx].getEnrolledCourses(enrolled, count);

    bool ok = consistencyChecker.checkStudentOverload(studentList[idx].getName(), maxCourses, count);
    
    if (ok)
        cout << "\nStudent " << studentList[idx].getName() << " is within limits (" << count << "/" << maxCourses << " courses)." << endl;
}

void checkAllStudentsLoad()
{
    if (totalStudents == 0)
    {
        cout << "\nNo students registered." << endl;
        return;
    }

    int maxCourses = getIntInput("Maximum allowed courses per student: ");
    
    consistencyChecker.clearConflicts();

    for (int i = 0; i < totalStudents; i++)
    {
        string enrolled[MAX_COURSES];
        int count;
        studentList[i].getEnrolledCourses(enrolled, count);
        consistencyChecker.checkStudentOverload(studentList[i].getName(), maxCourses, count);
    }

    consistencyChecker.displayConflicts();
}

void consistencyCheckerMenu()
{
    int choice;
    do
    {
        clearScreen();
        cout << "========== Consistency Checker ==========" << endl;
        cout << "1. Check Single Student Load" << endl;
        cout << "2. Check All Students Load" << endl;
        cout << "3. Display All Conflicts" << endl;
        cout << "4. Clear Conflicts" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "=========================================" << endl;

        choice = getValidChoice(0, 4);

        switch (choice)
        {
            case 1: checkStudentLoad(); break;
            case 2: checkAllStudentsLoad(); break;
            case 3: consistencyChecker.displayConflicts(); break;
            case 4: 
                consistencyChecker.clearConflicts();
                cout << "\nConflicts cleared!" << endl;
                break;
        }

        if (choice != 0) pauseScreen();
    } while (choice != 0);
}

// ==================== REPORTS ====================
void systemSummary()
{
    cout << "\n========== System Summary ==========" << endl;
    cout << "Total Students: " << totalStudents << "/" << MAX_STUDENTS << endl;
    cout << "Total Courses: " << totalCourses << "/" << MAX_COURSES << endl;
    cout << "Total Faculty: " << totalFaculty << "/" << MAX_FACULTY << endl;
    cout << "Total Rooms: " << totalRooms << "/" << MAX_ROOMS << endl;
    cout << "======================================" << endl;
}

void reportsMenu()
{
    int choice;
    do
    {
        clearScreen();
        cout << "========== Reports ==========" << endl;
        cout << "1. System Summary" << endl;
        cout << "2. List All Students" << endl;
        cout << "3. List All Courses" << endl;
        cout << "4. List All Faculty" << endl;
        cout << "5. List All Rooms" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "=============================" << endl;

        choice = getValidChoice(0, 5);

        switch (choice)
        {
            case 1: systemSummary(); break;
            case 2: viewAllStudents(); break;
            case 3: viewAllCourses(); break;
            case 4: viewAllFaculty(); break;
            case 5: viewAllRooms(); break;
        }

        if (choice != 0) pauseScreen();
    } while (choice != 0);
}

// ==================== MAIN MENU ====================
void mainMenu()
{
    int choice;
    do
    {
        clearScreen();
        cout << "===============================================" << endl;
        cout << "    UNIVERSITY MANAGEMENT SYSTEM" << endl;
        cout << "    Discrete Mathematics Module" << endl;
        cout << "===============================================" << endl;
        cout << "1.  Student Management" << endl;
        cout << "2.  Course Management" << endl;
        cout << "3.  Faculty Management" << endl;
        cout << "4.  Room Management" << endl;
        cout << "5.  Group Management (Combinations)" << endl;
        cout << "6.  Set Operations" << endl;
        cout << "7.  Relations" << endl;
        cout << "8.  Functions" << endl;
        cout << "9.  Logic Engine" << endl;
        cout << "10. Proof Verifier" << endl;
        cout << "11. Consistency Checker" << endl;
        cout << "12. Reports" << endl;
        cout << "0.  Exit" << endl;
        cout << "===============================================" << endl;

        choice = getValidChoice(0, 12);

        switch (choice)
        {
            case 1: studentManagementMenu(); break;
            case 2: courseManagementMenu(); break;
            case 3: facultyManagementMenu(); break;
            case 4: roomManagementMenu(); break;
            case 5: groupManagementMenu(); break;
            case 6: setOperationsMenu(); break;
            case 7: relationsMenu(); break;
            case 8: functionsMenu(); break;
            case 9: logicEngineMenu(); break;
            case 10: proofVerifierMenu(); break;
            case 11: consistencyCheckerMenu(); break;
            case 12: reportsMenu(); break;
            case 0:
                cout << "\nThank you for using University Management System!" << endl;
                cout << "Goodbye!" << endl;
                break;
        }
    } while (choice != 0);
}

// ==================== MAIN ====================
int main()
{
    cout << "===============================================" << endl;
    cout << "  Welcome to University Management System" << endl;
    cout << "  with Discrete Mathematics Integration" << endl;
    cout << "===============================================" << endl;
    
    pauseScreen();
    
    mainMenu();
    
    return 0;
}