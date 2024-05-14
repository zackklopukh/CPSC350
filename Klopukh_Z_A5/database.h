#ifndef DATABSE_H
#define DATABASE_H
#include "lazyBST.h"
#include "Student.h"
#include "Faculty.h"
#include <iostream>
#include <sstream>
#include <fstream>

class database {
    public:

    database();
    ~database();

    void printAllStudents();
    void printAllFaculty();
    void findStudentByID();
    void findFacultyByID();
    void addStudent();
    void deleteStudent();
    void addFaculty();
    void deleteFaculty();
    void changeStudentAdvisor();
    void removeAdviseeFromFaculty();
    void exitProgram();

    void runProgram();

    private:
    LazyBST<Student> *studentBST;
    LazyBST<Faculty> *facultyBST;
};

#endif