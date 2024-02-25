#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <iostream>
#include <cctype>
#include "Model.h"

using namespace std;

class Translator{

    public:
    Translator(); //default constructor
    ~Translator(); //default destructor

    string translateEnglishWord(string input);

    string translateEnglishSentence(string input);



    private:

    Model *myModel;

};

#endif