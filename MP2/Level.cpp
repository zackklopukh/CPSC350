#include "Level.h"

Level::Level() {

}

Level::Level( int gridSize, int pCoins, int pNothing, int pGoombas, int pKoopas, int pMushrooms, bool isLastLevel) {
    levelGridSize = gridSize;
    levelArray = new char*[levelGridSize];

    randomizer = mt19937(random_device{}());
    uniform_int_distribution<int> distribution(1, 100);

    for (int i = 0; i < levelGridSize; ++i) {
        levelArray[i] = new char[levelGridSize];
    }

    //filling the grid
    int tempRand = 0;
    for (int i = 0; i < levelGridSize; ++i) {
        for (int j = 0; j < levelGridSize; ++j) {
            tempRand = distribution(randomizer);

            //Range <pCoins, <pCoins+pNothing, <pCoins+pNothing+pGoombas, , <pCoins+pNothing+pGoombsa+pKoopas <pCoins+pNothing+pGoombas+ pKoopas+pMushrooms
            if (tempRand <= pCoins) {
                levelArray[i][j] = 'c';
            }
            else if (tempRand <= pCoins+pNothing) {
                levelArray[i][j] = 'x';
            }
            else if (tempRand <= pCoins+pNothing+pGoombas) {
                levelArray[i][j] = 'g';
            }
            else if (tempRand <= pCoins+pNothing+pGoombas+pKoopas) {
                levelArray[i][j] = 'k';
            }
            else if (tempRand <= pCoins+pNothing+pGoombas+pKoopas+pMushrooms) {
                levelArray[i][j] = 'm';
            }
        }
    }

    //add a boss and a pipe, not on same spot
    uniform_int_distribution<int> distributionGrid(0, levelGridSize - 1);

    //boss
    levelArray[distributionGrid(randomizer)][distributionGrid(randomizer)] = 'B';

    //if not last level, add pipe
    if (!isLastLevel) {
    int tempJ = 0;
    int tempI = 0;
        do {
            tempI = distributionGrid(randomizer);
            tempJ = distributionGrid(randomizer);
        } while (levelArray[tempI][tempJ] == 'b');
        levelArray[tempI][tempJ] = 'W';
    }
}

Level::~Level() {
    for (int i = 0; i < levelGridSize; ++i) {
        delete[] levelArray[i];
    }
    delete[] levelArray;
}

string Level::getLevelString() {
    string levelString = "";
    for (int i = 0; i < levelGridSize; ++i) {
        for (int j = 0; j < levelGridSize; ++j) {
            levelString += string(1, levelArray[i][j]);
        }
        levelString += "\n";
    }
    return levelString;
}

//This will print level with Mario
string Level::getLevelString(int x, int y) {
    char tempData = levelArray[x][y];
    string levelString = "";
    levelArray[x][y] = 'H';
    for (int i = 0; i < levelGridSize; ++i) {
        for (int j = 0; j < levelGridSize; ++j) {
            levelString += string(1, levelArray[i][j]);
        }
        levelString += "\n";
    }
    levelArray[x][y] = tempData;
    return levelString;
}

int Level::getGridDimension() {
    return levelGridSize;
}