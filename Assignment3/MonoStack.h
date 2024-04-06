/// @file  MonoStack.h
/// @brief This is a template file for a Monotonic Stack with either increasing or decreasing order.
/// @author Zack Klopukh, klopukh@chapman.edu

#ifndef MONOSTACK_H
#define MONOSTACK_H

#include<iostream>
#include <exception>

using namespace std;

template <class T>
class MonoStack{

    public:
        MonoStack(); //default constructor
        MonoStack(int maxSize); //overloaded constructor
        MonoStack(int maxSize, char o); //overloaded constructor
        ~MonoStack(); //destructor

        //core functions
        void push(T data);
        T pop();// return and remove
        T peek(); //aka top, just returns DOES NOT remove

        //aux/helper functions
        bool isEmpty();
        bool isFull();
        int getSize();

    private:
        int top;
        int mSize;
        T *myArray;
        char stackOrder;
};

template <class T>
MonoStack<T>::MonoStack(){
    mSize = 64; //default size of our stack
    top = -1;
    myArray = new T[mSize];
    stackOrder = 'i';
}

template <class T>
MonoStack<T>::MonoStack(int maxSize){
    mSize = maxSize;
    top = -1;
    myArray = new T[mSize];
    stackOrder = 'i';
}

template <class T>
MonoStack<T>::MonoStack(int maxSize, char o){
    mSize = maxSize;
    top = -1;
    myArray = new T[mSize];
    stackOrder = o;
}

template <class T>
MonoStack<T>::~MonoStack(){
    cout << "stack destroyed, garbage taken out has been" << endl;
    delete[] myArray;
}

template <class T>
void MonoStack<T>::push(T data){
    //check if stack is full
    if(isFull()){
        cout << " resizing stack" << endl;
        T *temp = new T[2*mSize];
        for(int i = 0; i < mSize; ++i){
            temp[i] = myArray[i]; //copy data from old array into new larger array
        }
        mSize *= 2; //shorthand for mSize = mSize * 2
        delete[] myArray;
        myArray = temp;
    }
    
    if (stackOrder == 'd')
    {
        while (!isEmpty() && data < peek()) {
            pop();
        }
    } else if (stackOrder == 'i') {
        while (!isEmpty() && data > peek()) {
            pop();
        }
    }
    else {
        throw runtime_error("stack order has an unexpected value.");
    }
    myArray[++top] = data;
}

template <class T>
T MonoStack<T>::pop(){
    //check if stack is empty
    if(isEmpty()){
        throw runtime_error("stack is empty, nothing to pop");
    }
    return myArray[top--];
}

template <class T>
T MonoStack<T>::peek(){
    //check if stack is empty
    if(isEmpty()){
        throw runtime_error("stack is empty, nothing to peek");
    }
    return myArray[top];
}

template <class T>
bool MonoStack<T>::isEmpty(){
    return (top == -1);
}

template <class T>
bool MonoStack<T>::isFull(){
    return (top == mSize-1);
}

template <class T>
int MonoStack<T>::getSize(){
    return top + 1;
}


#endif