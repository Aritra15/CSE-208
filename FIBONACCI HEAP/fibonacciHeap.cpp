#include <bits/stdc++.h>
#include "fibonacciHeap.h"
using namespace std;

void FibonacciHeap::insert(int key, int value)
{
    Node *node = new Node(key, value);
    if (maxNode != nullptr)
    {
        node->left = maxNode;
        node->right = maxNode->right;
        maxNode->right = node;
        node->right->left = node;
        if (node->key > maxNode->key)
        {
            maxNode = node;
        }
    }
    else
    {
        maxNode = node;
    }
    numOfNodes++;
    nodeMap[value] = node;
}


void FibonacciHeap::removeNode(Node *node)
{   
    if(node->right->left)
        node->right->left = node->left;
    if(node->left->right)
        node->left->right = node->right;
}

void FibonacciHeap::link(Node *child, Node *parent)
{
    removeNode(child);
    child->parent = parent;
    if (parent->child == nullptr)
    {
        parent->child = child;
        child->right = child;
        child->left = child;
    }
    else
    {
        child->left = parent->child;
        child->right = parent->child->right;
        parent->child->right = child;
        child->right->left = child;
    }
    parent->degree++;
    child->marked = false;
}

void FibonacciHeap::consolidate()
{

    int size = (int)log2(numOfNodes) + 1;

    Node *arr[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = nullptr;
    }
    Node *itr = maxNode;
    Node *temp = nullptr;
    Node *x = nullptr;
    Node *y = nullptr;
    int d = 0;
    int flag = 0;

    vector<Node *> rootlist;
    while (itr->right != maxNode)
    {
        rootlist.push_back(itr);
        itr = itr->right;
    }
    rootlist.push_back(itr);
    // for(auto i:rootlist){
    //     cout<<i->key<<endl;
    // }
    // cout<<maxNode->key<<endl;
    // print();

    for (auto root : rootlist)
    {
        temp = root;
        d = temp->degree;
        // cout<<d<<endl;
        // cout<<size<<endl;
        while (d < size && arr[d] != nullptr)
        {
            x = arr[d];
            if (temp->key < x->key)
            {
                y = temp;
                temp = x;
                x = y;
            }
            if (x == maxNode)
            {
                maxNode = temp;
            }
            link(x, temp);
            arr[d] = nullptr;
            d++;
        }
        arr[d] = temp;
    }
    // cout<<"test"<<endl;
    for (auto i : arr)
    {
        if (i != nullptr)
        {
            if (maxNode == nullptr)
            {
                maxNode = i;
            }
            else
            {
                if (i->key > maxNode->key)
                {
                    maxNode = i;
                }
            }
            // cout<<i->key<<endl;
        }
    }
}

int FibonacciHeap::extractMax()
{
    if (isEmpty())
    {
        return INT_MIN;
    }
    // print();
    Node *temp = maxNode;
    Node *child = nullptr;
    Node *itr = nullptr;
    if (temp->child != nullptr)
    {
        child = temp->child;
        int c = 0;
        // inserting children of maxNode into root list at right of maxNode
        while (child != temp->child || c == 0)
        {
            itr = child->right;
            removeNode(child);
            child->parent = nullptr;
            child->right = maxNode->right;
            child->left = maxNode;
            maxNode->right = child;
            child->right->left = child;
            child = itr;
            c = 1;
        }
    }
    removeNode(temp);
    
    numOfNodes--;

    if (temp == temp->right)
    {
        maxNode = nullptr;
    }
    else
    {
        maxNode = temp->right;
        //print();
        // cout<<"test"<<endl;
        consolidate();
    }
    nodeMap.erase(temp->value);
    return temp->key;
}


void FibonacciHeap::cut(Node *child, Node *parent)
{
    removeNode(child);
    parent->degree--;
    if (parent->degree == 0)
    {
        parent->child = nullptr;
    }
    else if (parent->child == child)
    {
        parent->child = child->right;
    }
    child->parent = nullptr;
    child->right = maxNode->right;
    child->left = maxNode;
    maxNode->right = child;
    child->right->left = child;
    child->marked = false;
}

void FibonacciHeap::cascadingCut(Node *node)
{
    Node *parent = node->parent;
    while (parent != nullptr)
    {
        if (node->marked == false)
        {
            node->marked = true;
            break;
        }
        else
        {
            cut(node, parent);
            node = parent;
            parent = node->parent;
        }
    }
}

void FibonacciHeap::increaseKey(Node *node, int key)
{
    if (key <= node->key)
    {
        // cout<<"New key is smaller than current key"<<endl;
        return;
    }
    node->key = key;
    Node *parent = node->parent;
    if (parent != nullptr && node->key > parent->key)
    {
        cut(node, parent);
        cascadingCut(parent);
    }
    if (node->key > maxNode->key)
    {
        maxNode = node;
    }
}

void FibonacciHeap::increaseKey(int value, int newKey)
{
    // Node *node = search(maxNode, value);
    Node *node = nodeMap[value];
    if (node == nullptr)
    {
        return;
    }
    increaseKey(node, newKey);
}

void FibonacciHeap::print(Node *itr)
{
    if (itr == nullptr)
    {
        return;
    }
    Node *itr2 = itr;
    do
    {

        if (itr2->parent == nullptr)
        {
            cout << "Tree " << counter++ << " : ";
        }

        if (itr2->child || itr2->parent == nullptr)
            cout << " (" << itr2->key << ", " << itr2->value << ") -> ";
        if (itr2->child)
        {

            Node *child = itr2->child;
            do
            {
                cout << " (" << child->key << "," << child->value << ")";
                if (child->right != itr2->child)
                    cout << ", ";
                child = child->right;
            } while (child != itr2->child);
            cout << endl;
        }
        else if (itr2->parent == nullptr)
        {
            cout << endl;
        }

        print(itr2->child);
        itr2 = itr2->right;
    } while (itr2 != itr);
}

void FibonacciHeap::print()
{
    counter = 1;
    print(maxNode);
}

Node *FibonacciHeap::search(Node *node, int value)
{
    Node *temp = node;
    Node *res = nullptr;
    if (node == nullptr)
    {
        // cout<<"Heap is empty"<<endl;
        return nullptr;
    }
    do
    {
        if (temp->value == value)
        {
            res = temp;
            break;
        }
        else
        {
            if (temp->child != nullptr)
            {
                res = search(temp->child, value);
            }
            if (res != nullptr)
            {
                break;
            }
            temp = temp->right;
        }
    } while (temp != node);
    return res;
}

void FibonacciHeap::deleteNode(Node *node)
{
    increaseKey(node, INT_MAX);
    // cout<<"here"<<endl;
    extractMax();
}

void FibonacciHeap::deleteNode(int value)
{
    //Node *node = search(maxNode, value);
    Node *node = nodeMap[value];
    if (node == nullptr)
    {
        return;
    }
    deleteNode(node);
}

Node* FibonacciHeap::findMax()
{
    if (isEmpty())
    {
        // cout<<"Heap is empty"<<endl;
        return nullptr;
    }
    return maxNode;
}



Node *FibonacciHeap::meld(Node *maxNodeOfHeap1, Node *maxNodeOfHeap2)
{
    if (maxNodeOfHeap1 == nullptr)
    {
        return maxNodeOfHeap2;
    }
    if (maxNodeOfHeap2 == nullptr)
    {
        return maxNodeOfHeap1;
    }
    Node *temp1 = maxNodeOfHeap1->right;
    maxNodeOfHeap1->right = maxNodeOfHeap2;
    Node *temp2 = maxNodeOfHeap2->left;
    maxNodeOfHeap2->left = maxNodeOfHeap1;
    temp1->left = temp2;
    temp2->right = temp1;

    if (maxNodeOfHeap1->key > maxNodeOfHeap2->key)
    {
        return maxNodeOfHeap1;
    }
    return maxNodeOfHeap2;
}

void FibonacciHeap::meld(FibonacciHeap heap2)
{
    maxNode = meld(maxNode, heap2.maxNode);
    numOfNodes += heap2.numOfNodes;
    nodeMap.insert(heap2.nodeMap.begin(), heap2.nodeMap.end());

    heap2.maxNode = nullptr;
    heap2.numOfNodes = 0;
    heap2.nodeMap.clear();
}