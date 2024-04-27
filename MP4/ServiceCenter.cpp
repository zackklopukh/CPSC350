#include "ServiceCenter.h"

ServiceCenter::ServiceCenter() {}

ServiceCenter::ServiceCenter(int nR, int nC, int nF) {
    registrarOffice = new Office(nR);
    cashierOffice = new Office(nC);
    financialOffice = new Office(nF);
}

ServiceCenter::~ServiceCenter() {
    delete registrarOffice;
    delete financialOffice;
    delete cashierOffice;
}

void ServiceCenter::addQueueCustomersForAllOffices() {
    registrarOffice->addQueueToWindow();
    cashierOffice->addQueueToWindow();
    financialOffice->addQueueToWindow();
}

void ServiceCenter::simTick() {
    registrarOffice->simTick();
    cashierOffice->simTick();
    financialOffice->simTick();
}

int ServiceCenter::totWindow5Plus() {
    int tot5Plus = 0;

    tot5Plus += registrarOffice->totWindow5Plus();
    tot5Plus += cashierOffice->totWindow5Plus();
    tot5Plus += financialOffice->totWindow5Plus();

    return tot5Plus;
}