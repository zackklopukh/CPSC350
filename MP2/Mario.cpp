#include "Mario.h"

// originally was going to have mario have private variables and use the
// getters and setters I gave, but it was much more sensible for mario's
// variables to be public as they are all he really represents.
// this means the getters and setters aren't very helpful.

Mario::Mario(){}

Mario::Mario(int intialLives) {
    numLives = intialLives;
    numCoins = 0;
    pwrLevel = 0;
    enemiesKilled = 0;
    x = 0;
    y = 0;
}

Mario::~Mario() {

}

//Getters
int Mario::getNumLives() {
    return numLives;
}

int Mario::getNumCoins() {
    return numCoins;
}

int Mario::getPwrLevel() {
    return pwrLevel;
}

//Setters
void Mario::setNumLives(int n) {
    numLives = n;
}

void Mario::setNumCoins(int n) {
    numCoins = n;
}

void Mario::setPwrLevel(int n) {
    pwrLevel = n;
}