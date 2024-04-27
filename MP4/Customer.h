#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "ListQueue.h"
#include <sstream>
#include <string>

class Customer {
    private:


    public:
    bool inOffice;
    bool atWindow;
    int idleTime;
    int totIdleTime;
    bool isFinished;
    int currOffice; // 0 1 2 index for which office in order they are in
    char* orderQ;
    int* timeQ;

    Customer();
    ~Customer();
    Customer(string instructions);
    Customer(char firstOffice, char secondOffice, char thirdOffice, int firstTime, int secondTime, int thirdTime);
};

#endif