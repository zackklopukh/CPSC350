#include "Student.h"
#include <iostream>

Student::Student() {}

Student::Student(string n_name, string n_level, string n_major, double n_gpa) {
    name = n_name;
    level = n_level;
    major = n_major;
    gpa = n_gpa;
    advisor = 0;
    createID();
}

Student::Student(int n_id) {
    id = n_id;
}

Student::~Student() {}

void Student::createID() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1000000, 1999999); // 1... range for person IDs
    id = dis(gen);
    cout << "here in code: " << id << endl;
}

bool Student::operator==(const Student& other) const {
    return this->id == other.id;
}

bool Student::operator!=(const Student& other) const {
    return this->id != other.id;
}

bool Student::operator<(const Student& other) const {
    return this->id < other.id;
}

bool Student::operator>(const Student& other) const {
    return this->id > other.id;
}

ostream& operator<<(std::ostream& os, const Student& student) {
    os << "Name: " << student.name  << ", ID: " << student.id << ", Level: " << student.level
       << ", Major: " << student.major << ", GPA: " << student.gpa << ", Advisor: " << student.advisor;
    return os;
}
