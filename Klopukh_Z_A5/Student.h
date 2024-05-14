#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <random>
#include "Faculty.h"

using namespace std;

class Student {
public:
    string major;
    double gpa;
    int advisor;
    int id;
    string name;
    string level;

    // Constructors
    Student();
    Student(string n_name, string n_level, string n_major, double n_gpa);
    Student(int n_id); // used to search for a student of this ID
    ~Student();

    bool operator==(const Student& other) const;
    bool operator!=(const Student& other) const;
    bool operator>(const Student& other) const;
    bool operator<(const Student& other) const;
    friend ostream& operator<<(std::ostream& os, const Student& student);


    void createID();


    // Other member functions specific to Student if needed
};

#endif
