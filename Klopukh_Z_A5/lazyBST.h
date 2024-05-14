#ifndef LAZYBST_H
#define LAZYBST_H

#include <iostream>
#include <sstream>
using namespace std;

template <class T>
class TreeNode {
    public:
        TreeNode();
        TreeNode(T k);
        virtual ~TreeNode();

        int leftDepth;
        int rightDepth;
        T key;
        TreeNode<T> *left;
        TreeNode<T> *right;
};

template<class T>
TreeNode<T>::TreeNode() {
    leftDepth = 0;
    rightDepth = 0;
    left = NULL;
    right = NULL;
    key = NULL;
}

template<class T>
TreeNode<T>::TreeNode(T k) {
    leftDepth = 0;
    rightDepth = 0;
    left = NULL;
    right = NULL;
    key = k;
}

template<class T>
TreeNode<T>::~TreeNode() {
    left = NULL;
    right = NULL;
}

template<class T>
class LazyBST {
    public:
    LazyBST();
    virtual ~LazyBST();
    void recursiveDestructor(TreeNode<T> *node);

    void insert(T value);
    bool contains(T value);
    T* searchGet(T value);
    bool deleteNode(T k);
    TreeNode<T> *getSuccessor(TreeNode<T> *d);

    void checkBalance(TreeNode<T> *d);
    void balanceTree(TreeNode<T>* d);
    bool isEmpty();
    T getMin();
    T getMax();

    void recPrint(TreeNode<T> *node);
    void printTree();

    void recReturnPrint(TreeNode<T>* node, std::ostringstream& os);
    ostringstream returnPrintTree();

    void inOrderToArray(TreeNode<T>* root, T* arr, int& idx);
    int countNodes(TreeNode<T>* root);
    void balanceTreeHelper(T* arr, int start, int end);

    private:

        bool balanceInProgess;
        TreeNode<T> *root;

};

template <class T>
LazyBST<T>::LazyBST() {
    balanceInProgess = false;
    root = NULL;
}

template <class T>
LazyBST<T>::~LazyBST() {
    recursiveDestructor(root);
}

template <class T>
void LazyBST<T>::recursiveDestructor(TreeNode<T> *node) {

    if (node != NULL) {
        recursiveDestructor(node->right);
        recursiveDestructor(node->left);
    }
    delete node;
}

template <class T>
void LazyBST<T>::recPrint(TreeNode<T> *node) {

    if (node != NULL) {
        // in order because we cout before traversing left then right
        recPrint(node->left);
        cout << node->key << endl;
        recPrint(node->right);
    }
}

template <class T>
void LazyBST<T>::printTree() {
    recPrint(root);
}

template <class T>
void LazyBST<T>::recReturnPrint(TreeNode<T>* node, ostringstream& os) {
    if (node != NULL) {
        recReturnPrint(node->left, os);
        os << node->key << endl;
        recReturnPrint(node->right, os);
    }
}

template <class T>
ostringstream LazyBST<T>::returnPrintTree() {
    ostringstream os;
    recReturnPrint(root, os);
    return os;
}

template <class T>
void LazyBST<T>::inOrderToArray(TreeNode<T>* root, T* arr, int& idx) {
    if (root != NULL) {
        inOrderToArray(root->left, arr, idx);
        arr[idx++] = root->key;
        inOrderToArray(root->right, arr, idx);
    }
}

template<class T>
bool LazyBST<T>::isEmpty() {
    return (root == NULL);
}

template<class T>
T LazyBST<T>::getMin() {
    if (isEmpty())
        return NULL;

    TreeNode<T> *current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current->key;
}

template<class T>
T LazyBST<T>::getMax() {
    if (isEmpty())
        return NULL;

    TreeNode<T> *current = root;
    while (current->right != NULL) {
        current = current->right;
    }
    return current->key;
}

template<class T>
void LazyBST<T>::insert(T value) {
    TreeNode<T> *node = new TreeNode<T>(value);

    if (isEmpty()) {
        root = node;
    } else{
        //tree had more than one node, add it in place

        TreeNode<T> *current = root;
        TreeNode<T> *parent = NULL;

        while (true) {
            parent = current;
            if (value < current->key) {
                //go left
                current->leftDepth++;
                current = current->left;

                if (current == NULL) {
                    //found insertion point
                    parent->left = node;
                    break;
                }
            } 
            else {
                //go right
                current->rightDepth++;
                current = current->right;

                if (current == NULL) {
                    parent->right = node;
                    break;
                }
            }
        }
    }
    checkBalance(root);
}

//search method O(log(n))
template <class T>
bool LazyBST<T>::contains(T value) {

    if (isEmpty())
        return false;

    TreeNode<T> *current = root;

    while (current->key != value) {
        if (value < current->key)
            current = current->left;
        else {
            current = current->right;
        }

        if (current == NULL) {
            return false;
        }
    }
    return true;
}

template <class T>
T* LazyBST<T>::searchGet(T value) {

    if (isEmpty())
        return NULL;

    TreeNode<T> *current = root;

    while (current->key != value) {
        if (value < current->key)
            current = current->left;
        else {
            current = current->right;
        }

        if (current == NULL) {
            return NULL;
        }
    }
    return &(current->key);
}

template <class T>
bool LazyBST<T>::deleteNode(T k) {

    if (isEmpty())
        return false;
    
    TreeNode<T> *current = root;
    TreeNode<T> *parent = NULL;
    bool isLeft = true;

    while (current->key != k) {
        parent = current;

        if (k < current->key) {
            isLeft = true;
            current = current->left;
        } else {
            isLeft = false;
            current = current->right;
        }

        if (current == NULL)
            return false;
    }

    //we made it out of the loop, we found the node
    //now delete

    if (current->right == NULL && current->left == NULL) {
        if (current == root) {
            root = NULL;
        } else if(isLeft) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
    }

    else if (current->right == NULL) {
        //has 1 left child
        if (current == root) {
            root = current->left;
        } else if(isLeft) {
            parent->left = current->left;
        } else {
            parent->right = current->left;
        }
    }

    else if (current->left == NULL) {
        //has 1 RIGHT child
        if (current == root) {
            root = current->right;
        } else if(isLeft) {
            parent->left = current->right;
        } else {
            parent->right = current->right;
        }
    }

    //NODE HAS 2 CHILDREN
    else {
        TreeNode<T> *successor = getSuccessor(current);

        if (current == root) {
            root = successor;
        }
        else if (isLeft) {
            parent->left = successor;
        } else {
            parent->right = successor;
        }
        successor->left = current->left;

        current->right = NULL;
        current->left = NULL;
    }
    delete current;

    TreeNode<T> *ancestor = root;
    while (ancestor != NULL) {
        if (isLeft)
            ancestor->leftDepth++;
        else
            ancestor->rightDepth++;
        ancestor = (isLeft ? ancestor->left : ancestor->right);
    }
    checkBalance(root);

    return true;
}


template <class T>
TreeNode<T>* LazyBST<T>::getSuccessor(TreeNode<T> *d) {
    
    TreeNode<T> *sp = d;
    TreeNode<T> *successor = d;
    TreeNode<T> *current = d->right;

    while(current != NULL) {
        sp = successor;
        successor = current;
        current = current->left;
    }
    //once we get here we've found the successor
    //now check if successor is the descendant of the right child
    if (successor != d->right) {
        sp->left = successor->right;
        successor->right = d->right;
    }
    return successor;
}

template <class T>
void LazyBST<T>::checkBalance(TreeNode<T>* d) {
    if (d == NULL || balanceInProgess)
        return;

    checkBalance(d->left); // Check balance of left subtree
    checkBalance(d->right); // Check balance of right subtree

    int leftSubtreeDepth = d->leftDepth;
    int rightSubtreeDepth = d->rightDepth;

    // Check if the tree is imbalanced
    if (abs(leftSubtreeDepth - rightSubtreeDepth) > 1.5) {
        // Tree is imbalanced, balance it
        balanceTree(root);
    }
}

template <class T>
void LazyBST<T>::balanceTree(TreeNode<T>* d) {
    int nodeCount = countNodes(root);
    T* arr = new T[nodeCount];

    int idx = 0;
    inOrderToArray(root, arr, idx); // Assuming you have a function to fill the array in inorder traversal

    // Delete existing tree
    recursiveDestructor(root);
    root = NULL;

    balanceInProgess = true;
    balanceTreeHelper(arr, 0, nodeCount - 1);
    balanceInProgess = false;

    delete[] arr;

}

template <class T>
int LazyBST<T>::countNodes(TreeNode<T>* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

template <class T>
void LazyBST<T>::balanceTreeHelper(T* arr, int start, int end) {
    if (start > end) {
        return;
    }

    int mid = (start + end) / 2;
    insert(arr[mid]);

    balanceTreeHelper(arr, start, mid-1);
    balanceTreeHelper(arr, mid+1, end);
}

#endif