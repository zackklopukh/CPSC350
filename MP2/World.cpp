#include "World.h"

World::World() {}

World::World(int nLevels, int gSize, int iLives, int pCoins, int pNothing, int pGoombas, int pKoopas, int pMushrooms, string outFileName) {

    // https://stackoverflow.com/questions/34126262/use-random-in-a-c-class
    randomizer = mt19937(random_device{}());

    outputFile = new ofstream(outFileName);
    totalLevels = nLevels;
    int gridSize = gSize;
    int intLives = iLives;
    int perCoins = pCoins;
    int perNothing = pNothing;
    int perGoombas = pGoombas;
    int perKoopas = pKoopas;
    int perMushrooms = pMushrooms;

    allLevels = new Level[totalLevels];
    isLastLevel = false; //last level has no warp pipe

    //Create n levels
    *outputFile << "Preview of level(s)\n";
    for (int i = 0; i < totalLevels; ++i) {
        if (i == totalLevels - 1) {
            isLastLevel = true;
        }
        Level *tempLevel = new Level(gridSize, perCoins, perNothing, perGoombas, perKoopas, perMushrooms, isLastLevel);
        allLevels[i] = *tempLevel;
        *outputFile << tempLevel->getLevelString();
        *outputFile << "============\n";

    }

    //Create our mario
    myMario = new Mario(intLives);

    //start at level 0 indexed by 0
    currLevelIndex = 0;
    //completeRun
    completeRun();

    outputFile->close();

}


World::~World() {
    delete[] allLevels;
    delete myMario;
}

//complete run will have mario play through each level until he wins or dies
void World::completeRun() {

    while (startLevel() == 0) {}
}

// start level does all things that happen before mario does his first move
// return 0 - Play next level, else don't
int World::startLevel() {
    // add mario to a random location in the grid
    uniform_int_distribution<int> marioLocation(0, allLevels[0].getGridDimension() - 1);
    myMario->x = marioLocation(randomizer);
    myMario->y = marioLocation(randomizer);

    *outputFile << "Mario is starting in position (" << myMario->x << "," << myMario->y << ")\n";
    *outputFile << "=================\n";

    //play turn is where mario will play through each level
    return playTurn();
}

//playTurn loops until mario dies (1) moves to next level (0) or wins (2)
int World::playTurn() {
    int result = 0;

    while (result == 0 || (result == 1 && myMario->numLives > 0)) {

        //display things before interaction
        //FIX
        *outputFile << allLevels[currLevelIndex].getLevelString(myMario->x, myMario->y);

        *outputFile << "Level " << currLevelIndex << ". ";
        *outputFile << "Mario is at position (" << myMario->x << "," << myMario->y << "). ";
        *outputFile << "Mario is at power level " << myMario->getPwrLevel() << ". ";

        //interactWith takes mario's location and interacts with the object there
        // it does't need to take as parameter because I switched how mario's
        // variables are accessed, but I kept the code the same.
        result = interactWith(myMario->x,myMario->y);

        //check if mario gains a life
        if (myMario->numCoins == 20) {
            *outputFile << " Mario converts 20 coins into a life! ";
            myMario->numCoins = 0;
            myMario->numLives++;
        }
        if (myMario->enemiesKilled == 7) {
            *outputFile << " Mario has 7 kills on the same life, +1 life! ";
            myMario->enemiesKilled = 0;
            myMario->numLives++;
        }

        //check if mario lost life
        if (myMario->pwrLevel < 0) {
            if (myMario->numLives > 0) {
                *outputFile << "Mario lost a life. ";
                myMario->numLives--;
                myMario->pwrLevel = 0;
            } else {
                *outputFile << "Mario died and is out of lifes.\n";
                return 1;
            }
        }

        //display lives and coins after interaction
        *outputFile << "Mario has " << myMario->numLives << " lives left. Mario has " << myMario->numCoins << " coin(s). ";

        //mario will either move, stay put or warp.
        uniform_int_distribution<int> moveDirection(1, 4);
        switch (result) {
            case 0:
                //MOVE CASE
                switch (moveDirection(randomizer)) {
                    case 1:
                        *outputFile << "Mario will go right.\n";
                        if (myMario->y == allLevels->getGridDimension()-1) {
                            myMario->y = 0;
                        } else {
                            myMario->y++;
                        }
                        break;
                    case 2:
                        *outputFile << "Mario will go left.\n";
                        if (myMario->y == 0) {
                            myMario->y = allLevels->getGridDimension()-1;
                        } else {
                            myMario->y--;
                        }
                        break;
                    case 3:
                        *outputFile << "Mario will go down.\n";
                        if (myMario->x == allLevels->getGridDimension()-1) {
                            myMario->x = 0;
                        } else {
                            myMario->x++;
                        }
                        break;
                    case 4:
                        *outputFile << "Mario will go up.\n";
                        if (myMario->x == 0) {
                            myMario->x = allLevels->getGridDimension()-1;
                        } else {
                            myMario->x--;
                        }
                        break;
                    default:
                        *outputFile << "Issue moving mario.\n";
                        break;
                }
                break;
            case 1:
                *outputFile << "Mario will stay put.\n";
                break;
            case 2:
                *outputFile << "Mario will WARP.\n";
                break;
            case 3:
                *outputFile << "Mario will stay put.\n";
                break;
            default:
                break;
        }
        *outputFile << "=================\n";
    }

    //check if mario died
    if (myMario->numLives == 0) {
        *outputFile << "Mario is dead. GAME OVER.\n";
        return -1;
    }
    //check if mario beat the game
    if (currLevelIndex == totalLevels - 1) {
        *outputFile << "WE BEAT THE GAME :)\n";
        return 2;
    } else {
        *outputFile << "Moving onto next level.\n";
        currLevelIndex++;
        return 0;
    }
}

//without seperate classes, I use the char to then call a seperate method per each interaction
int World::interactWith(int x, int y) {
    switch (allLevels[currLevelIndex].levelArray[x][y]) {
        case 'c':
            return interactWithCoin();
            break;
        case 'm':
            return interactWithMushroom();
            break;
        case 'g':
            return interactWithGoomba();
            break;
        case 'k':
            return interactWithKoopa();
            break;
        case 'x':
            return interactWithNothing();
            break;
        case 'B':
            return interactWithBoss();
            break;
        case 'W':
            return interactWithPipe();
            break;
        default:
            //
            break;
    }
}

//interactions return 
// 0 to move one
// 1 to stay put
// 2 to signify using pipe
// 3 to signify beating boss

int World::interactWithNothing() {
    *outputFile << "The position was empty. ";
    return 0;
}

int World::interactWithCoin() {
    int marioCoins = myMario->getNumCoins();
    myMario->setNumCoins(++marioCoins);
    allLevels[currLevelIndex].levelArray[myMario->x][myMario->y] = 'x';
    *outputFile << "Mario collected a coin. ";
    return 0;
}

int World::interactWithMushroom() {
    if (int temp = myMario->pwrLevel < 2) {
        myMario->pwrLevel++;
    }
    allLevels[currLevelIndex].levelArray[myMario->x][myMario->y] = 'x';
    *outputFile << "Mario ate a mushroom. ";
    return 0;
}

int World::interactWithGoomba() {
    uniform_int_distribution<int> fightSim(1, 100);
    int chance = fightSim(randomizer);
    if (chance <= 80) {
        *outputFile <<"Mario fought a Goomba and won. ";
        allLevels[currLevelIndex].levelArray[myMario->x][myMario->y] = 'x';
        myMario->enemiesKilled++;
        return 0;
    }
    *outputFile << "Mario fought a Goomba and lost. ";
    myMario->pwrLevel--;
    return 0;
}

int World::interactWithKoopa() {
    uniform_int_distribution<int> fightSim(1, 100);
    int chance = fightSim(randomizer);
    if (chance <= 65) {
        *outputFile << "Mario fought a Koopa and won. ";
        allLevels[currLevelIndex].levelArray[myMario->x][myMario->y] = 'x';
        myMario->enemiesKilled++;
        return 0;
    }
    myMario->pwrLevel--;
    *outputFile << "Mario fought a Koopa and lost. ";
    return 0;
}

int World::interactWithBoss() {
    uniform_int_distribution<int> fightSim(1, 100);
    int chance = fightSim(randomizer);
    if (chance <= 50) {
        *outputFile << "Mario fought the BOSS and won. ";
        myMario->enemiesKilled++;
        return 3;
    }
    myMario->pwrLevel -= 2;
    *outputFile << "Mario fought the BOSS and lost. ";
    return 1;   
}

int World::interactWithPipe() {
    *outputFile << "Mario used a pipe. ";
    return 2;    
}