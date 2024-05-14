#ifndef FACULTY_H
#define FACULTY_H

#include <string>
#include <random>
#include "DblList.h"

class Faculty {
public:

    int id;
    string name;
    string level;
    string department;
    DblList<int> *advisees;

    Faculty(); 
    Faculty(string n_name, string n_level, string n_department);
    Faculty(int n_id); // used to search for a student of this ID
    ~Faculty();

    void createID();

    bool operator==(const Faculty& other) const;
    bool operator!=(const Faculty& other) const;
    bool operator>(const Faculty& other) const;
    bool operator<(const Faculty& other) const;
    friend ostream& operator<<(std::ostream& os, const Faculty& faculty);
};

#endif
