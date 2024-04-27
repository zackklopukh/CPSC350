    #include "Window.h"
    
    Window::Window() {
        occupied = false;
        idleTime = 0;
        totTime = 0;
        occupiedTime = 0;
        totStudents = 0;
        totStudentWaitInQueue = 0;
    }

    Window::~Window() {
        delete currCustomer;
    }

    bool Window::isOpen() {
        return !occupied;
    }

    //add new user to the window
    void Window::newUser(Customer *Customer) {
        currCustomer = Customer;
        occupied = true;
        currCustomer->atWindow = true;
        totStudents++;
        totStudentWaitInQueue += currCustomer->idleTime;

        if (currCustomer->idleTime > longestWaitingCustomer)
            longestWaitingCustomer = currCustomer->idleTime;

        currCustomer->totIdleTime += currCustomer->idleTime;
        currCustomer->idleTime = 0;
    }
    
    void Window::simTick() {
        if (occupied) { //someone is at window
            currCustomer->timeQ[currCustomer->currOffice]--;
            occupiedTime++;
            if (currCustomer->timeQ[currCustomer->currOffice] < 1) {  // check if user finishes office this tick
                currCustomer->inOffice = false;
                currCustomer->atWindow = false;
                currCustomer->currOffice++;
                occupied = false;
                if (currCustomer->currOffice > 2)
                    currCustomer->isFinished = true;

            }
        } else { // nobody is at window
            idleTime++;
        }
        totTime++;
    }