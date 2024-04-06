/// @file  SpeakerView.cpp
/// @brief SpeakerView is an object class that takes a file representing a seating
/// chart and displays who can see the front of the room (row 0 being closest)
/// @author Zack Klopukh, klopukh@chapman.edu

#include "SpeakerView.h"

SpeakerView::SpeakerView(string fileName) {
    nRows = 0;
    nCols = 0;
    //gather the columns and rows of the seating arrangement
    calculateSize(fileName);

    //create empty 2D array of the size of the seating arrangement
    seatingArray = new double *[nRows];
    for (int i = 0; i < nRows; i++) {
        seatingArray[i] = new double[nCols];
    }

    //add the values into our seatingArray
    addValuesToArray(fileName);

    //Use MonoStack to show results of SpeakerView
    showResults();
}
SpeakerView::~SpeakerView() {
    for (int i = 0; i < nRows; i++) {
        delete[] seatingArray[i];
    }
    delete[] seatingArray;
}

void SpeakerView::calculateSize(string fileName) {
    ifstream readFile(fileName);
    //error checking one file will suffice
    if (!readFile.is_open()) {
        cerr << "Error in opening File." << endl;
    }

    string fileString;

    //using the first row to calculate total columns
    getline(readFile, fileString);

    for (int i = 0; i < fileString.length(); i++) {
        if (isspace(fileString[i])) {
            nCols++;
        }
    }
    // for each space in a line, a new double should follow.
    // the first digit doesn't have a space represntation, so add an extra
    nCols++;

    // add back the line we took out
    readFile.clear();
    readFile.seekg(0);

    while (getline(readFile, fileString)) {
        if (isdigit(fileString[0]))
            nRows++;
    }
    readFile.close();
}

void SpeakerView::addValuesToArray(string fileName) {
    ifstream readFile(fileName);
    //error checking one file will suffice
    if (!readFile.is_open()) {
        cerr << "Error in opening File." << endl;
    }

    int currRow = 0;
    int currCol = 0;

    string currData = "";

    while (readFile && (currRow < nRows)) {
        //additionally checking if currRow is less than nRows will help in error checking

        while (readFile && (currCol < nCols)) {
        readFile >> currData;
        seatingArray[currRow][currCol++] = stod(currData);
        currData = "";
        }
        currCol = 0;
        currRow++;
    }
}

void SpeakerView::showResults() {
    MonoStack<double>* mStack = new MonoStack<double>(nCols+1, 'i');

    int currCol = 0;
    int currRow = 0;

    for (int currCol = 0; currCol < nCols; ++currCol) {
        for (int currRow = nRows - 1; currRow > -1; --currRow) {
            mStack->push(seatingArray[currRow][currCol]);
        }
        cout << "In column " << currCol << " there are " << to_string(mStack->getSize()) << " that can see. Their heights are: ";

        while (!mStack->isEmpty()) {
            cout << mStack->pop() << " ";
        }
        cout << "inches." << endl;
    }
}