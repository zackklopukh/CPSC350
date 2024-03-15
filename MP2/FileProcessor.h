#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include "World.h"
#include <iostream>
#include <fstream>

using namespace std;

class FileProcessor{

    public:
    FileProcessor();
    ~FileProcessor();

    void processFile();

    private:

    //helper methods
    void readFile(string fileName);
    void createGame();

    int* gameData;
    World* mainWorld;

};

#endif