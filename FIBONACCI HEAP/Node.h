#include<bits/stdc++.h>
using namespace std;
class Node{
    public:
    int key;
    int value;
    bool marked;
    Node *left;
    Node *right;
    Node *parent;
    Node* child;
    int degree;
    Node(int key, int value){
        this->key = key;
        this->value = value;
        this->marked = false;
        this->left = this;
        this->right = this;
        this->parent = NULL;
        this->child = NULL;
        this->degree = 0;
    }
};