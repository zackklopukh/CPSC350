#include "Faculty.h"
#include <iostream>

Faculty::Faculty() {}

Faculty::Faculty(string n_name, string n_level, string n_department) {
    name = n_name;
    level = n_level;
    department = n_department;
    advisees = new DblList<int>();
    createID();
}

Faculty::Faculty(int n_id) {
    id = n_id;
}

Faculty::~Faculty() {}

void Faculty::createID() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(2000000, 2999999); // 2... range for faculty IDs
    id = dis(gen);
    cout <<  "Faculty created. ID: " << id << endl;
}

bool Faculty::operator==(const Faculty& other) const {
    return this->id == other.id;
}
bool Faculty::operator!=(const Faculty& other) const {
    return this->id != other.id;
}

bool Faculty::operator<(const Faculty& other) const {
    return this->id < other.id;
}

bool Faculty::operator>(const Faculty& other) const {
    return this->id > other.id;
}

ostream& operator<<(std::ostream& os, const Faculty& faculty) {
    os << "Name: " << faculty.name << ", ID: " << faculty.id << ", Level: " << faculty.level
       << ", Department: " << faculty.department;
    os << "\nList of Advisees: ";
    faculty.advisees->printList(os);
    return os;
}