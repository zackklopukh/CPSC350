#ifndef OFFICE_H
#define OFFFICE_H

#include "Window.h"

class Office {
    public:
    Office();
    Office(int nWindows);
    ~Office();

    void addCustomerToQueue(Customer *customerToAdd);
    void addQueueToWindow();
    void simTick();

    float getMeanCustWait();
    float getMeanWindIdle();

    float getLongestCustWait();
    float getLongestWindowWait();

    int totWindow5Plus();

    string printStats();

    private:
    int numWindows;
    Window** windowArray;
    ListQueue<Customer*> *waitingList;
    
};

#endif