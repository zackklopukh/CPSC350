#include "FileProcessor.h"
#include "Translator.h"

FileProcessor::FileProcessor() {
     myTranslator = new Translator();
}

FileProcessor::~FileProcessor() {
    delete myTranslator;
}

void FileProcessor::processFile(string inFile, string outFile) {

    //read files twice, once to display once to translate (bcus I can only use primatives)
    ifstream displayFile(inFile);
    ifstream translateFile(inFile);

    //error checking one file will suffice
    if (!displayFile.is_open()) {
        cerr << "Error in opening File." << endl;
    }

    //create a string consisting of the current line
    string line;

    //ofstream is the html file, with basic html heading
    ofstream htmlFile(outFile);
    htmlFile << "<!DOCTYPE html><html><head></head><body>";

    //first grab each line and display with BOLD text in html
    while (getline(displayFile, line)) {
        htmlFile << "<p><strong>" << line << "</strong></p>" << endl << endl;
    }

    htmlFile << "<p><b></b><br></p>";

    //second grab each line, translate, and display in ITALICS in html
    while (getline(translateFile, line)) {
        string translatedText = myTranslator->translateEnglishSentence(line);
        htmlFile << "<p><em>" << translatedText << "</em></p>" << endl << endl;
    }
    //how to read file https://www.udacity.com/blog/2021/05/how-to-read-from-a-file-in-cpp.html
    //I used your attached html tutorial to figure out the ofstream file
    htmlFile.close();
}