#ifndef WINDOW_H
#define WINDOW_H

#include "Customer.h"

class Window {
    public:
    Window();
    ~Window();

    bool isOpen();
    void newUser(Customer *costumer);
    void simTick();

    bool occupied;
    int timeLeft;
    int idleTime;
    int totTime;
    int occupiedTime;
    int totStudents;
    int totStudentWaitInQueue;
    int longestWaitingCustomer;

    private:
    Customer *currCustomer;
};

#endif