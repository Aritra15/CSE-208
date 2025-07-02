#include <bits/stdc++.h>
#include "Nodes.h"

using namespace std;
template <class T>
class RedBlackTree
{
private:
    Node<T> *root;
    int nodeCount;

    void leftRotate(Node<T> *node);
    void rightRotate(Node<T> *node);
    void Insert(Node<T> *node);
    void InsertFix(Node<T> *node);

    void Iteration(Node<T> *node);

    void clear(Node<T> *node);

    bool isLeftChild(Node<T> *node){ return node->parent->lChild == node;}

    Node<T> *findSibling(Node<T> *node);
    Node<T> *findSmallest(Node<T> *node);

    void erase(Node<T> *node, int key);
    Node<T> *find(int key, int flag, Node<T> *node);
    void deleteNodeWithOneChild(Node<T> *node);
    void exchangeNodeWithChild(Node<T> *node);
    void deleteBlackCase1(Node<T> *node);
    void deleteBlackCase2(Node<T> *node);
    void deleteBlackCase3(Node<T> *node);
    void deleteBlackCase4(Node<T> *node);
    void deleteBlackCase5(Node<T> *node);
    void deleteBlackCase6(Node<T> *node);

    void print(Node<T> *root);

public:
    RedBlackTree()
    {
        root = new Node<T>(INT_MIN, "", NULL, NULL, NULL, true);
        nodeCount = 0;
    }
    void Insert(int key, string data)
    {
        Node<T> *node = new Node<T>(key, data);
        Insert(node);
        nodeCount++;
    }

    void clear()
    {
        clear(root);
        this->root = new Node<T>(INT_MIN, "", NULL, NULL, NULL, true);
        nodeCount = 0;
    }

    int size() { return nodeCount; }

    bool Empty() { return nodeCount == 0; }

    bool find(T key);
    bool find(T key, string value);

    void erase(int key){
        erase(root, key);
        nodeCount--;
    }

    void Iteration(){Iteration(root);}

    void print();
};