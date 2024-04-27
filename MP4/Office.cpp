#include "Office.h"

Office::Office() {}

Office::Office(int nWindows) {
    numWindows = nWindows;
    windowArray = new Window*[numWindows];
    waitingList = new ListQueue<Customer*>;

    for (int i = 0; i < numWindows; ++i) {
        windowArray[i] = new Window();
    }
}

Office::~Office() {
     for (int i = 0; i < numWindows; ++i) {
        delete windowArray[i];
    }
    delete[] windowArray;
}

//add customer to the queue for windows
void Office::addCustomerToQueue(Customer* addCustomerToQueue) {
    waitingList->insert(addCustomerToQueue);
}

//remove peeople from queue and add to available windows
void Office::addQueueToWindow() {
    if (!waitingList->isEmpty()) {
        for (int i = 0; i < numWindows; ++i) {
            if (!windowArray[i]->occupied) {
                windowArray[i]->occupied = true;
                windowArray[i]->newUser(waitingList->remove());
                // should be here
            }

            if (waitingList->isEmpty())
                break;
        }
    }
}

//simulate a tick in an office
void Office::simTick() {
    for (int i = 0; i < numWindows; ++i) {
        windowArray[i]->simTick();
    }
}

//from here below, these will get the data and stats from simulations

float Office::getMeanCustWait() {
    float totWaitTime = 0;
    int totCustomers = 0;

    for (int i = 0; i < numWindows; ++i) {
        totCustomers += windowArray[i]->totStudents;
        totWaitTime += windowArray[i]->totStudentWaitInQueue;
    }
    return totWaitTime / totCustomers;
}

float Office::getMeanWindIdle() {
    float totWaitTime = 0;

    for (int i = 0; i < numWindows; ++i) {
        totWaitTime += windowArray[i]->idleTime;
    }
    return totWaitTime / numWindows;
}

float Office::getLongestCustWait() {
    int longest = 0;

    for (int i = 0; i < numWindows; ++i) {
        if (windowArray[i]->longestWaitingCustomer > longest)
        longest = windowArray[i]->longestWaitingCustomer;
    }
    return longest;
}
float Office::getLongestWindowWait() {
    int longest = 0;

    for (int i = 0; i < numWindows; ++i) {
        if (windowArray[i]->idleTime > longest)
        longest = windowArray[i]->idleTime;
    }
    return longest;
}

string Office::printStats() {
    ostringstream printStatement;
    printStatement << "Mean student wait time: "  << getMeanCustWait() << " tick(s)\n";
    printStatement << "Mean window idle time: " << getMeanWindIdle() << " tick(s)\n";
    printStatement << "Longest student wait time: " << getLongestCustWait() << " tick(s)\n";
    printStatement << "Longest window idle time: " << getLongestWindowWait() << " tick(s)\n";

    return printStatement.str();
}

int Office::totWindow5Plus() {
    int total = 0;

    for (int i = 0; i < numWindows; ++i) {
        if (windowArray[i]->idleTime > 4)
        total++;
    }
    return total;
}