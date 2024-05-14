#include "database.h"

database::database() {
    studentBST = new LazyBST<Student>;
    facultyBST = new LazyBST<Faculty>;
}
database::~database() {
    delete studentBST;
    delete facultyBST;
}

void database::printAllStudents(){
    studentBST->printTree();
}
void database::printAllFaculty(){
    facultyBST->printTree();
}
void database::findStudentByID(){
    int studentID;
    cout << "Enter the ID of the student you want to print: ";
    cin >> studentID;

    // error checking
    if (cin.fail()) {
        cout << "Invalid input. Please enter a valid ID." << endl;
        cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        return;
    }
    
    Student tempStudent(studentID);
    Student *locatedStudent = studentBST->searchGet(tempStudent);
    if (locatedStudent == NULL) {
        cout << "Student with ID " << studentID << " not found." << endl;
    } else {
        cout << *locatedStudent << endl;
    }
}
void database::findFacultyByID(){
    int facultyID;
    cout << "Enter the ID of the faculty you want to print: ";
    cin >> facultyID;

    // error checking
    if (cin.fail()) {
        cout << "Invalid input. Please enter a valid ID." << endl;
        cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        return;
    }
    
    Faculty tempFaculty(facultyID);
    Faculty *locatedFaculty = facultyBST->searchGet(tempFaculty);
    if (locatedFaculty == NULL) {
        cout << "Faculty with ID " << facultyID << " not found." << endl;
    } else {
        cout << *locatedFaculty << endl;
    }
}

void database::addStudent() {
    string name, level, major;
    double gpa;
    cin.ignore();

    cout << "Enter student's name: ";
    getline(cin, name);

    cout << "Enter student's level: ";
    getline(cin, level);

    cout << "Enter student's major: ";
    getline(cin, major);

    while (true) {
        cout << "Enter student's GPA: ";
        if (cin >> gpa) {
            break;
        } else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid GPA." << endl;
        }
    }
    Student newStudent(name, level, major, gpa);
    studentBST->insert(newStudent);
}

void database::deleteStudent(){
    int studentID;
    cout << "Enter the ID of the student you want to delete: ";
    cin >> studentID;

    // error checking
    if (cin.fail()) {
        cout << "Invalid input. Please enter a valid ID." << endl;
        cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        return;
    }
    
    Student tempStudent(studentID);
    if (studentBST->deleteNode(tempStudent)) {
        cout << "Student with ID " << studentID << " has been successfully deleted." << endl;
    } else {
        cout << "Student with ID " << studentID << " not found." << endl;
    }
}

void database::addFaculty(){
    string name, level, department;
    cin.ignore();

    cout << "Enter faculty's name: ";
    getline(cin, name);

    cout << "Enter faculty's level: ";
    getline(cin, level);

    cout << "Enter faculty's department: ";
    getline(cin, department);

    Faculty newFaculty(name, level, department);
    facultyBST->insert(newFaculty);
}

void database::deleteFaculty(){
    int facultyID;
    cout << "Enter the ID of the faculty you want to delete: ";
    cin >> facultyID;

    // error checking
    if (cin.fail()) {
        cout << "Invalid input. Please enter a valid ID." << endl;
        cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        return;
    }
    
    Faculty tempFaculty(facultyID);
    if (facultyBST->deleteNode(tempFaculty)) {
        cout << "Faculty with ID " << facultyID << " has been successfully deleted." << endl;
    } else {
        cout << "Faculty with ID " << facultyID << " not found." << endl;
    }
}
void database::changeStudentAdvisor(){
    int studentID;
    cout << "Enter the ID of the student: ";
    cin >> studentID;

    // error checking
    if (cin.fail()) {
        cout << "Invalid input. Please enter a valid ID." << endl;
        cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        return;
    }

    Student tempStudent(studentID);
    Student *foundStudent = studentBST->searchGet(tempStudent);
    if (foundStudent == NULL) {
        cout << "STUDENT not found." << endl;
        return;
    }

    int facultyID;
    cout << "Enter the ID of the ADVISOR: ";
    cin >> facultyID;

    // error checking
    if (cin.fail()) {
        cout << "Invalid input. Please enter a valid ID." << endl;
        cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        return;
    }

    Faculty tempFaculty(facultyID);
    Faculty *foundFaculty = facultyBST->searchGet(tempFaculty);
    if (foundFaculty == NULL) {
        cout << "ADVISOR not found." << endl;
        return;
    }
    // IF HERE IN CODE, STUDENT AND ADVISOR EXIST

    if (foundStudent->advisor != 0) { //already has advisee
        Faculty tempRemoveFac(foundStudent->advisor);
        facultyBST->searchGet(tempRemoveFac)->advisees->removeNode(studentID);
    } // so get rid of him as advisee for that faculty

    foundStudent->advisor = facultyID;
    foundFaculty->advisees->insertBack(studentID);

    cout << "Advisor Added." << endl;
}

void database::removeAdviseeFromFaculty(){
     int facultyID;
    cout << "Enter the ID of the faculty: ";
    cin >> facultyID;

    // error checking
    if (cin.fail()) {
        cout << "Invalid input. Please enter a valid ID." << endl;
        cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        return;
    }

    Faculty tempFaculty(facultyID);
    Faculty *foundFaculty = facultyBST->searchGet(tempFaculty);
    if (foundFaculty == NULL) {
        cout << "ADVISOR not found." << endl;
        return;
    }

    int studentID;
    cout << "Enter the ID of the student: ";
    cin >> studentID;

    // error checking
    if (cin.fail()) {
        cout << "Invalid input. Please enter a valid ID." << endl;
        cin.clear(); // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        return;
    }

    if (foundFaculty->advisees->find(studentID) == -1) {
        cout << "This is not an advisee of this Faculty." << endl;
        return;
    }

    Student tempStudent(studentID);
    Student *foundStudent = studentBST->searchGet(tempStudent);
    if (foundStudent == NULL) {
        cout << "STUDENT not found." << endl;
        return;
    }
    // IF HERE IN CODE, STUDENT AND ADVISOR EXIST

    foundStudent->advisor = 0;
    foundFaculty->advisees->removeNode(studentID);

    cout << "Advisee Removed." << endl;
}

void database::exitProgram() {

    ostringstream os;

    os << "Students:\n";
    os << studentBST->returnPrintTree().str();

    os << "\nFaculty:\n";
    os << facultyBST->returnPrintTree().str();

    ofstream outFile("runLog.txt");
    if (outFile.is_open()) {
        outFile << os.str();
        outFile.close();
        cout << "Exting Program. Data saved in runLog.txt" << endl;
    } else {
        cerr << "Unable to open file for writing" << std::endl;
    }
    //exit(0);
}

void database::runProgram() {
    int decision;

    while (true) {
        cout << "\n1. Print all students and their information (sorted by ascending id #)" << endl;
        cout << "2. Print all faculty and their information (sorted by ascending id #)" << endl;
        cout << "3. Find and display student information given the student id" << endl;
        cout << "4. Find and display faculty information given the faculty id" << endl;
        cout << "5. Add a new student" << endl;
        cout << "6. Delete a student given the id" << endl;
        cout << "7. Add a new faculty member" << endl;
        cout << "8. Delete a faculty member given the id" << endl;
        cout << "9. Change a student’s advisor given the student id and the new faculty id" << endl;
        cout << "10. Remove an advisee from a faculty member given the ids" << endl;
        cout << "11. Exit" << endl;
        cout << "Choose an action (1-11): ";
        cin >> decision;

        // error check
        if (cin.fail() || decision < 1 || decision > 11) {
            cout << "Invalid input. Please enter a number from 1 to 11." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch (decision) {
            case 1:
                printAllStudents();
                break;
            case 2:
                printAllFaculty();
                break;
            case 3:
                // Call method to print all students and their information
                findStudentByID();
                break;
            case 4:
                // Call method to print all faculty and their information
                findFacultyByID();
                break;
            case 5:
                // Call method to find and display student information given the student id
                addStudent();
                break;
            case 6:
                // Call method to find and display faculty information given the faculty id
                deleteStudent();
                break;
            case 7:
                addFaculty();
                break;
            case 8:
                deleteFaculty();
                break;
            case 9:
                changeStudentAdvisor();
                break;
            case 10:
                removeAdviseeFromFaculty();
                break;
            case 11:
                exitProgram();
                return;
                break;
            default:
                cout << "Invalid input. Please enter a number from 1 to 11." << endl;
                break;
        }
    }
}
