#include "FileProcessor.h"

// most of this code is from MP1
// it gets the input, and creates a game to play by the rules

FileProcessor::FileProcessor() {
    gameData = new int[8];
}

FileProcessor::~FileProcessor() {
    delete[] gameData;
    delete mainWorld;
}

void FileProcessor::processFile() {

    //gather input for text file name
    string fileName;
    cout << "Name of the file with your game rules:   ";
    cin >> fileName;

    //read the file
    readFile(fileName);

    //Create a world with the game input
    createGame();  
}

//this method reads the game settings from file into gameData[]
void FileProcessor::readFile(string fileName) {

    ifstream gameFile(fileName);
    //error checking one file will suffice
    if (!gameFile.is_open()) {
        cerr << "Error in opening File." << endl;
    }

    
    for (int i = 0; i < 8; ++i) {
        if (!(gameFile >> gameData[i])) {
            cerr << "Error reading integer from file.\n";
        }
    }
    gameFile.close();
}

//this method simply initializes the mainWorld with whatever gameData has been processed
void FileProcessor::createGame() {
    string fileOutName;
    cout << "Name of the output file name:   ";
    cin >> fileOutName;

    mainWorld = new World(gameData[0], gameData[1], gameData[2], gameData[3], gameData[4], gameData[5], gameData[6], gameData[7], fileOutName);
}