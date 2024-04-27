#ifndef SERVICECENTER_H
#define SERVICECENTER_H

#include "Office.h"

class ServiceCenter {
    public:

    ServiceCenter();
    ServiceCenter(int nR, int nC, int nF);
    ~ServiceCenter();

    void addQueueCustomersForAllOffices();
    void simTick();
    int totWindow5Plus();

    Office *registrarOffice;
    Office *cashierOffice;
    Office *financialOffice;

    private:
};


#endif