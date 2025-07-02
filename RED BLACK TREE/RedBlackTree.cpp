#include <bits/stdc++.h>
#include "RedBlackTree.h"
#include "color.hpp"
using namespace std;

template <class T>
Node<T> *RedBlackTree<T>::findSmallest(Node<T> *node)
{
    if (node->lChild->isNullLeaf)
    {
        return node;
    }
    else
        return findSmallest(node->lChild);
}

template <class T>
Node<T> *RedBlackTree<T>::findSibling(Node<T> *node)
{
    if (isLeftChild(node))
    {
        return node->parent->rChild;
    }
    else
    {
        return node->parent->lChild;
    }
}

template <class T>
Node<T> *RedBlackTree<T>::find(int key, int flag, Node<T> *node)
{
    
    while (node != NULL)
    {
        if (node->key < key)
        {
            node = node->rChild;
        }
        else if (node->key > key)
        {
            node = node->lChild;
        }
        else
        {
            return node;
        }
    }
    return nullptr;
}

template <class T>
bool RedBlackTree<T>::find(T key)
{
    Node<T> *node = root;
    while (node->lChild != NULL && node->rChild != NULL)
    {
        if (node->key < key)
        {
            node = node->rChild;
        }
        else if (node->key > key)
        {
            node = node->lChild;
        }
        else
        {
            return true;
        }
    }
    return false;
}

template <class T>
bool RedBlackTree<T>::find(T key, string value)
{
    Node<T> *node = root;
    while (node != NULL)
    {
        if (node->key < key)
        {
            node = node->rChild;
        }
        else if (node->key > key)
        {
            node = node->lChild;
        }
        else
        {
            if (node->data == value)
                return true;
            else
                node = node->rChild;
        }
    }
    return false;
}





template <class T>
void RedBlackTree<T>::leftRotate(Node<T> *x)
{
    Node<T> *y = x->rChild;
    x->rChild = y->lChild;

    if (y->lChild != nullptr)
        y->lChild->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->lChild)
        x->parent->lChild = y;
    else
        x->parent->rChild = y;

    y->lChild = x;
    x->parent = y;
}

template <class T>
void RedBlackTree<T>::rightRotate(Node<T> *x)
{
    Node<T> *y = x->lChild;
    x->lChild = y->rChild;
    if (x->lChild != NULL)
    {
        x->lChild->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL)
    {
        root = y;
    }
    else if (x->parent->lChild == x)
    {
        x->parent->lChild = y;
    }
    else
    {
        x->parent->rChild = y;
    }
    x->parent = y;
    y->rChild = x;
}

template <class T>
void RedBlackTree<T>::Insert(Node<T> *node)
{
    // cout<<node->key<<endl;
    Node<T> *Parent = NULL;
    Node<T> *x = root;
    while (x->lChild != NULL && x->rChild)
    {
        Parent = x;
        if (x->key > node->key)
        {
            x = x->lChild;
        }
        else if (x->key < node->key)
        {
            x = x->rChild;
        }
        else
        {
            x->data = node->data;
            return;
        }
    }
    node->parent = Parent;

    if (node->parent == NULL)
    {
        root = node;
        node->color = BLACK;
    }
    else if (Parent->key > node->key)
    {
        Parent->lChild = node;
    }
    else
    {
        Parent->rChild = node;
    }
    // Iteration();
    // cout<<root->key;
    InsertFix(node);
}

template <class T>
void RedBlackTree<T>::InsertFix(Node<T> *z)
{
    while (z->parent && z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->lChild)
        {
            Node<T> *y = z->parent->parent->rChild;
            if (y && y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->rChild)
                {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        }
        else
        {
            Node<T> *y = z->parent->parent->lChild;
            if (y && y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->lChild)
                {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

template <class T>
void RedBlackTree<T>::Iteration(Node<T> *node)
{
    if (node->lChild != NULL && node->rChild != NULL)
    {
        Iteration(node->lChild);
        cout << node->key << " => " << node->data << " " << node->color << endl;
        Iteration(node->rChild);
    }
}

template <class T>
void RedBlackTree<T>::clear(Node<T> *node)
{
    if (node != NULL)
    {
        clear(node->lChild);
        clear(node->rChild);
        delete node;
    }
}

template <class T>
void RedBlackTree<T>::exchangeNodeWithChild(Node<T> *node)
{
    // considering the node has at max 1 child
    Node<T> *child = (node->rChild->isNullLeaf) ? node->lChild : node->rChild;
    // if(child!=NULL)
    child->parent = node->parent;
    if (node->parent == NULL)
        root = child;
    else if (isLeftChild(node))
    {
        node->parent->lChild = child;
    }
    else
    {
        node->parent->rChild = child;
    }
}

template <class T>
void RedBlackTree<T>::erase(Node<T> *root, int key)
{

    Node<T> *node = find(key, 1, root);
    if (node == NULL)
    {
        return;
    }

    if (node->lChild->isNullLeaf || node->rChild->isNullLeaf)
    {
        deleteNodeWithOneChild(node);
    }
    else
    {
        Node<T> *inOrderSuccessor = findSmallest(node->rChild);
        node->key = inOrderSuccessor->key;
        node->data = inOrderSuccessor->data;
        erase(node->rChild, inOrderSuccessor->key);
    }
}

template <class T>
void RedBlackTree<T>::deleteNodeWithOneChild(Node<T> *node)
{
    Node<T> *child = (node->rChild->isNullLeaf) ? node->lChild : node->rChild;
    exchangeNodeWithChild(node);

    if (node->color == BLACK)
    {
        if (!child->isNullLeaf && child->color == RED)
        {
            child->color = BLACK;
        }
        else
        {
            deleteBlackCase1(child);
        }
    }
    delete node;
}

template <class T>
void RedBlackTree<T>::deleteBlackCase1(Node<T> *node)
{
    if (node->parent == NULL)
    {
        return;
    }
    else
    {
        deleteBlackCase2(node);
    }
}

template <class T>
void RedBlackTree<T>::deleteBlackCase2(Node<T> *node)
{
    Node<T> *sibling = findSibling(node);
    if (node->parent->color == BLACK && sibling->color == RED && sibling->lChild->color == BLACK && sibling->rChild->color == BLACK)
    {
        sibling->color = BLACK;
        node->parent->color = RED;
        if (isLeftChild(node))
        {
            leftRotate(node->parent);
        }
        else
        {
            rightRotate(node->parent);
        }
    }
    deleteBlackCase3(node);
}

template <class T>
void RedBlackTree<T>::deleteBlackCase3(Node<T> *node)
{
    Node<T> *sibling = findSibling(node);
    if (node->parent->color == BLACK && sibling->color == BLACK && sibling->lChild->color == BLACK && sibling->rChild->color == BLACK)
    {
        sibling->color = RED;
        deleteBlackCase1(node->parent);
    }
    else
    {
        deleteBlackCase4(node);
    }
}

template <class T>
void RedBlackTree<T>::deleteBlackCase4(Node<T> *node)
{
    Node<T> *sibling = findSibling(node);
    if (sibling->color == BLACK && node->parent->color == RED && sibling->lChild->color == BLACK && sibling->rChild->color == BLACK)
    {
        sibling->color = RED;
        node->parent->color = BLACK;
    }
    else
    {
        deleteBlackCase5(node);
    }
}

template <class T>
void RedBlackTree<T>::deleteBlackCase5(Node<T> *node)
{
    Node<T> *sibling = findSibling(node);
    if (sibling->color == BLACK)
    {
        if (isLeftChild(node) && sibling->lChild->color == RED && sibling->rChild->color == BLACK)
        {
            sibling->color = RED;
            sibling->lChild->color = BLACK;
            rightRotate(sibling);
        }
        else if (!isLeftChild(node) && sibling->rChild->color == RED && sibling->lChild->color == BLACK)
        {
            sibling->color = RED;
            sibling->rChild->color = BLACK;
            leftRotate(sibling);
        }
    }
}

template <class T>
void RedBlackTree<T>::deleteBlackCase6(Node<T> *node)
{
    Node<T> *sibling = findSibling(node);
    sibling->color = sibling->parent->color;
    sibling->parent->color = BLACK;
    if (isLeftChild(node))
    {
        sibling->rChild->color = BLACK;
        leftRotate(node->parent);
    }
    else
    {
        sibling->rChild->color = RED;
        rightRotate(node->parent);
    }
}

template <class T>
void RedBlackTree<T>::print()
{
    cout << "(";
    print(root);
    cout << ")" << endl;
}
template <class T>
void RedBlackTree<T>::print(Node<T> *p)
{
    if (p->lChild == NULL && p->rChild == NULL)
        return;
    string s = to_string(p->key) + "_" + p->data;
    if (p->color == RED)
    {
        cout << dye::red(s);
    }
    else
    {
        cout << s;
    }
    if (p->lChild->isNullLeaf && p->rChild->isNullLeaf)
    {
        return;
    }
    cout << "(";
    print(p->lChild);
    cout << ",";
    print(p->rChild);
    cout << ")";
}
