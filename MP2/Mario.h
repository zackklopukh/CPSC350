#ifndef MARIO_H
#define MARIO_H

#include <iostream>
#include <fstream>

using namespace std;

class Mario{

    public:
    Mario();
    Mario(int intialLives);
    ~Mario();

    int getNumLives();
    int getNumCoins();
    int getPwrLevel();

    void setNumLives(int n);
    void setNumCoins(int n);
    void setPwrLevel(int n);

    //these are marios x and y position
    int x;
    int y;
    int enemiesKilled;
    unsigned int numLives;
    unsigned int numCoins;
    int pwrLevel;

    private:

};

#endif