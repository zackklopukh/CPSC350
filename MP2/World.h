#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include<fstream>
#include "Level.h"
#include "Mario.h"

using namespace std;

class World{

    public:
    World();
    World(int nLevels, int gridSize, int intLives, int pCoins, int pNothing, int pGoombas, int pKoopas, int pMushrooms, string outFileName);
    ~World();

    private:

    int startLevel();
    int playTurn();
    void completeRun();

    int interactWith(int x, int y);
    int interactWithNothing();
    int interactWithCoin();
    int interactWithMushroom();
    int interactWithGoomba();
    int interactWithKoopa();
    int interactWithBoss();
    int interactWithPipe();

    bool isLastLevel;
    int totalLevels;
    int currLevelIndex;

    ofstream *outputFile;
    mt19937 randomizer;
    Level *allLevels;
    //Level *currLevel;
    Mario *myMario;
};

#endif