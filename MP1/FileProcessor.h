#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <iostream>
#include <fstream>
#include "Translator.h"

using namespace std;

class FileProcessor{

    public:
    FileProcessor();
    ~FileProcessor();

    void processFile(string inFile, string outFile);

    private:

    Translator *myTranslator;
};

#endif