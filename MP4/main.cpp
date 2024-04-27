#include "FileProcessor.h"

int main(int argc ,char **argv){

    if (argc < 2) {
        cerr << "No file was entered in the cmd line" << endl;
        return 1;
    }

    FileProcessor *fp = new FileProcessor();
    string fileInput = argv[1];
    fp->processFile(fileInput);
    delete fp;

}