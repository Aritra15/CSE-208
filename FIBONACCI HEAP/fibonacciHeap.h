#include <bits/stdc++.h>
#include "Node.h"
using namespace std;
int counter = 1;
class FibonacciHeap
{
    Node *maxNode;
    int numOfNodes;
    unordered_map<int, Node *> nodeMap;

    void removeNode(Node *node);

    void link(Node *child, Node *parent);

    void consolidate();

    void cut(Node *child, Node *parent);

    void cascadingCut(Node *node);

    void deleteNode(Node *node);

    Node *search(Node *node, int value);

    void increaseKey(Node *node, int key);

    void print(Node *itr);

public:
    FibonacciHeap()
    {
        maxNode = nullptr;
        numOfNodes = 0;
    }

    bool isEmpty() { return maxNode == nullptr; }

    int extractMax();

    void insert(int key, int value);

    Node* findMax();

    void print();

    void deleteNode(int value);

    void increaseKey(int value, int newKey);

    Node *meld(Node *maxNodeOfHeap1, Node *maxNodeOfHeap2);

    void meld(FibonacciHeap heap2);
};