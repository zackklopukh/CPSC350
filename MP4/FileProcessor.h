#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <iostream>
#include <fstream>
#include "ServiceCenter.h"
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

class FileProcessor{

    public:
    FileProcessor();
    ~FileProcessor();

    void processFile(string inFile);
    private:

    void runSimulation(); //for each hour run sim, update times etc.

    ServiceCenter *myCenter;
};

#endif