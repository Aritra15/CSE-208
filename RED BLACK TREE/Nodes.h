#include<bits/stdc++.h>
using namespace std;

enum Color {RED,BLACK};

template<class T>
class Node{
    public:
    T key;
    string data;
    Node<T>* lChild;
    Node <T>* rChild;
    Node<T>* parent;
    Color color;
    bool isNullLeaf;

    Node(T key,string data,Node<T> * lChild,Node <T> * rChild,Node<T>* parent,bool isNullLeaf){
        this->key=key;
        this->data=data;
        this->lChild=lChild;
        this->rChild=rChild;
        this->parent=parent;
        color = BLACK;
        this->isNullLeaf = isNullLeaf;
    }
    Node(T key,string data){
        this->key=key;
        this->data=data;
        this->lChild=new Node<T>(INT_MIN,"",NULL,NULL,this,true);
        this->rChild=new Node<T>(INT_MIN,"",NULL,NULL,this,true);
        this->parent=NULL;
        color = RED;
        isNullLeaf = false;
    }
    

};