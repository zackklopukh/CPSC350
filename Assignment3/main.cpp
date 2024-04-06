#include "MonoStack.h"
#include "SpeakerView.h"

int main(int argc ,char **argv){

    if (argc < 2) {
        cerr << "No file was entered in the cmd line" << endl;
        return 1;
    }
    
    string fileInput = argv[1];
    SpeakerView *sv = new SpeakerView(fileInput);

    delete sv;
}