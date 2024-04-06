#ifndef SPEAKERVIEW_H
#define SPEAKERVIEW_H

#include "MonoStack.h"
#include <fstream>

class SpeakerView {

    public:
        SpeakerView(string fileName);
        ~SpeakerView();

        void ProcessFile(string fileName);
        void calculateSize(string fileName);
        void addValuesToArray(string fileName);
        void showResults();

    private:
        double** seatingArray;
        int nRows;
        int nCols;

};

#endif