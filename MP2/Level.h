#ifndef LEVEL_H
#define LEVEL_H

#include "Mario.h"
#include <iostream>
#include <random>

using namespace std;

class Level{

    public:
    Level();
    Level(int gridSize, int pCoins, int pNothing, int pGoombas, int pKoopas, int pMushrooms, bool isLastLevel);
    ~Level();

    int getGridDimension();
    //level without mario
    string getLevelString();
    //level with mario's locaiton for 'H'
    string getLevelString(int x, int y);

    char** levelArray;

    private:

    char** fillGrid(char** emptyArray, int pCoins, int pNothing, int pGoombas, int pKoopas, int pMushrooms);

    mt19937 randomizer;
    int levelGridSize;

};

#endif