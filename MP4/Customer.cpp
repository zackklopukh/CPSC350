#include "Customer.h"

Customer::Customer() {
    // inOffice = false;
    // // using R C F 1 10 5 seperate and add to the queues correctly
    // orderQ = new char[3];
    // timeQ = new int[3];
}

Customer::Customer(char firstOffice, char secondOffice, char thirdOffice, int firstTime, int secondTime, int thirdTime) {
    isFinished = false;
    currOffice = 0;
    inOffice = false;
    atWindow = false;
    idleTime = 0;
    totIdleTime = 0;

    orderQ = new char[3]{firstOffice, secondOffice, thirdOffice};
    timeQ = new int[3]{firstTime, secondTime, thirdTime};
}

Customer::~Customer() {
    delete[] orderQ;
    delete[] timeQ;
}