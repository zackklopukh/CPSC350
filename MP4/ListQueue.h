// ListQueue template

#ifndef LISTQUEUE_H
#define LISTQUEUE_H
#include <iostream>
#include <exception>
#include "DblList.h"

using namespace std;


template <class T>
class ListQueue {

    public:

        ListQueue(); //default constructor
        ~ListQueue(); // destructor

        //core functions
        void insert(T d); // aka enqueue()
        T remove(); //dequeue()

        //aux helper functions
        T peek(); //view front, dont remove
        bool isEmpty();
        unsigned int getSize();

    private:

        unsigned int numElements;
        DblList<T> *myDLL;

};

template <class T>
ListQueue<T>::ListQueue() {
    numElements = 0;
    myDLL = new DblList<T>();
}

template<class T>
ListQueue<T>::~ListQueue() {
    delete myDLL;
}

template<class T>
void ListQueue<T>::insert(T d) {

    myDLL->insertBack(d);
    numElements++;
}

template<class T>
T ListQueue<T>::remove() {
    if (isEmpty()) {
        throw runtime_error("queue is empty");
    }

    numElements--;
    return myDLL->removeFront();
}

template<class T>
T ListQueue<T>::peek() {
    if (isEmpty()) {
        throw runtime_error("queue is empty");
    }

    return myDLL->front->data;
}

template<class T>
bool ListQueue<T>::isEmpty() {
    return (numElements == 0);
}

template<class T>
unsigned int ListQueue<T>::getSize() {
    return numElements;
}

// template<class T>
// void ListQueue<T>::printArray() {

//     cout << "Q SIZE: " << numElements << endl;
//     cout << "FRONT: " << front << endl;
//     cout << "REAR: " << rear << endl;

//     for (int i = 0; i < mSize; ++i) {
//         cout << "Q["<< i <<"]: " << myQueue[i];
//         if (i != mSize - 1) {
//             cout << " | ";
//         }
//     }
//     cout << endl;
// }
    
#endif