#include "Interact.h"

// I could've made each in-game objects their own class with a parent abstract class, giving them all
// unique interact methods, but instead I made an interact class that does similar in one class.
// It isn't as clean, but it was what I had already done and is still conisderably readable.

// make interact take the world and mario

Interact::Interact() {}

Interact::~Interact() {}

void Interact::interactWith(Mario mario, char object) {
    switch (object) {
        case 'c':
            //
            break;
        case 'm':
            //
            break;
        case 'g':
            //
            break;
        case 'k':
            //
            break;
        case 'x':
            //
            break;
        case 'b':
            //
            break;
        case 'w':
            //
            break;
        default:
            //
            break;
    }
}

void Interact::interactWithNothing(Mario mario) {

}

void Interact::interactWithCoin(Mario mario) {
    int marioCoins = mario.getNumCoins();
    mario.setNumCoins(++marioCoins);
    cout << "Mario collected a coin" << endl;
}

void Interact::interactWithMushroom(Mario mario) {
    
}

void Interact::interactWithGoomba(Mario mario) {
    
}

void Interact::interactWithKoopa(Mario mario) {
    
}

void Interact::interactWithBoss(Mario mario) {
    
}

void Interact::interactWithPipe(Mario mario) {
    
}
