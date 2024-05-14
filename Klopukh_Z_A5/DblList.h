#ifndef DDLLIST_H
#define DDLLIST_H

#include <iostream>
using namespace std;

template <class T>
class ListNode {

    public:
    ListNode();
    ListNode(T d);
    ~ListNode();
    ListNode<T> *next;
    ListNode<T> *prev;
    T data;

    private:
};

template <class T>
ListNode<T>::ListNode() {}

template <class T>
ListNode<T>::ListNode(T d) {
    data = d;
    next = NULL;
    prev = NULL;
}

template <class T>
ListNode<T>::~ListNode() {
    prev = NULL;
    next = NULL;
}

template <class T>
class DblList {

    public:
        DblList();
        ~DblList();

        void insertFront(T d);
        void insertBack(T d);

        //int getFront();

        T removeFront();
        T removeBack();
        T removeNode(T value);

        int find(T value);
        bool isEmpty();
        unsigned int getSize();

        void printList(bool isPrintLink);
        ostream& printList(ostream& os) const;

    private:
        ListNode<T> *front;
        ListNode<T> *back;
        unsigned int size;
};

template <class T>
DblList<T>::DblList() {
    front = NULL;
    back = NULL;
    size = 0;
}

template <class T>
DblList<T>::~DblList() {
    ListNode<T> *current = front;

    while (current != NULL) {
        ListNode<T> *next = current->next;
        delete current;
        current = next;
    }

    front = NULL;
    back = NULL;
    size = 0;
}

template <class T>
void DblList<T>::insertFront(T d) {
    ListNode<T> *node = new ListNode<T>(d);
    
    if (isEmpty()) {
        back = node;
    } else {
        front->prev = node;
        node->next = front;
    }
    front = node;
    size++;
}

template <class T>
void DblList<T>::insertBack(T d) {
    ListNode<T> *node = new ListNode<T>(d);
     if (isEmpty()) {
        front = node;
    } else {
        back->next = node;
        node->prev = back;
    }
    back = node;
    size++;
}

template <class T>
bool DblList<T>::isEmpty() {
    return (size == 0);
}

template <class T>
unsigned int DblList<T>::getSize() {
    return size;
}

template <class T>
T DblList<T>::removeFront() {

    if (isEmpty()) {
        cerr << "T is empty" << endl;
        return T();
    }

    ListNode<T> *temp = front;

    if (front->next == NULL) {
        //one node in list
        back = NULL;
    } else {
        //more than one in list
        front->next->prev = NULL;
    }

    front = front->next;
    temp->next = NULL;
    T data = temp->data;
    size--;

    delete temp;
    return data;
}

template <class T>
T DblList<T>::removeBack() {

    if (isEmpty()) {
        cerr << "list is empty" << endl;
        return T();
    }

    ListNode<T> *temp = back;

    if (back->prev == NULL) {
        //one node in list
        front = NULL;
    } else {
        //more than one in list
        back->prev->next = NULL;
    }

    back = back->prev;
    temp->prev = NULL;
    T data = temp->data;
    size--;

    delete temp;
    return data;
}


template <class T>
int DblList<T>::find(T value) {
    int pos = -1;

    ListNode<T> *curr = front;
    while (curr != NULL) {
        ++pos;
        if(curr->data == value)
            break;

        curr = curr->next;
    }
    if (curr == NULL) {
        pos = -1;
    }

    return pos;
}

template <class T>
T DblList<T>::removeNode(T value) {

    if (isEmpty()) {
        cerr << "invalid position or empty list" << endl;
        return T();
    }

    int idx = 0;
    ListNode<T> *curr = front;

    while (curr->data != value) {
        curr = curr->next;
        
        if (curr == NULL) {
            cout << "couldn't find item in list" << endl;
            return T();
        }
    }
    //here we found the node to be deleted

    if (curr == front && curr == back) {
        front = NULL;
        back = NULL;
    }
    else if (curr == front) { //front
        front = curr->next;
        front->prev = NULL;
    }
    else if (curr == back) { //back
        back = curr->prev;
        back->next = NULL;
    } else { //between
       curr->prev->next = curr->next;
       curr->next->prev = curr->prev;
    }

    curr->next = NULL;
    curr->prev = NULL;
    T temp = curr->data;
    size--;

    delete curr;
    return temp;
}

template <class T>
ostream& DblList<T>::printList(ostream& os) const {
    ListNode<T>* current = front;
    while (current != nullptr) {
        os << current->data << " ";
        current = current->next;
    }
    return os;
}

#endif