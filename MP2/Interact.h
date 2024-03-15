#ifndef INTERACT_H
#define INTERACT_H

#include "Mario.h"
#include "World.h"
#include <iostream>
#include <fstream>

using namespace std;

class Interact{

    public:
    Interact();
    Interact(World pWorld, Mario pMario);
    ~Interact();

    void interactWith(Mario mario, char object);

    private:

    void interactWithNothing(Mario mario);
    void interactWithCoin(Mario mario);
    void interactWithMushroom(Mario mario);
    void interactWithGoomba(Mario mario);
    void interactWithKoopa(Mario mario);
    void interactWithBoss(Mario mario);
    void interactWithPipe(Mario mario);

    World *world;
    Mario *mario;
};

#endif