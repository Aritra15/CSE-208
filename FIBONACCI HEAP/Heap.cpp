#include <bits/stdc++.h>
#include "fibonacciheap.cpp"
using namespace std;

class priorityQueue
{
    FibonacciHeap heap;

public:
    void make_heap()
    {
        heap = FibonacciHeap();
    }
    bool is_Empty()
    {
        if (heap.isEmpty())
        {
            cout << "Heap is empty" << endl;
            return true;
        }
        else
        {
            cout << "Heap is not empty" << endl;
            return false;
        }
    }
    void insert(int key, int value)
    {
        heap.insert(key, value);
    }
    int extractMax()
    {

        int maxValue = heap.extractMax();
        if (maxValue != INT_MIN)
            cout <<"Extracted: " <<maxValue << endl;
        return maxValue;
    }
    void increaseKey(int value, int new_key)
    {
        heap.increaseKey(value, new_key);
    }

    void Delete(int value)
    {
        heap.deleteNode(value);
    }

    priorityQueue meld(priorityQueue &heap1, priorityQueue &heap2)
    {
        heap1.heap.meld(heap2.heap);
        return heap1;
    }

    void find_max()
    {
        Node *max = heap.findMax();
        if (max != nullptr)
        {
            cout<<"Max Node: ";
            cout << "("<<max->key <<","<<max->value<<")"<< endl;
        }
        else
        {
            cout << "Heap is empty" << endl;
        }
    }

    void print()
    {
        heap.print();
    }

    void test()
    {
        // try extracting max from empty heap
        //freopen("MyOutput.txt", "w", stdout);
        extractMax();
        Delete(10);
        find_max();
        for (int i = 0; i < 10; i++)
        {
            insert(i, i * 10);
        }
        print();
        // try to delete some keys which are not present in the heap
        for (int i = 120; i > 50; i -= 10)
        {
            Delete(i);
        }
        print();
        find_max();
        increaseKey(0, 100);
        find_max();
        // try to increase key of a non-existent key
        increaseKey(0, 50);
        find_max();
        // try to decrease a key
        cout<<"increase called!";
        increaseKey(100, 50);
        print();
        is_Empty();
        for(int i=0;i<=50;i+=10){
            Delete(i);
        }
        extractMax();
        Delete(50);
        Delete(10);
        is_Empty();
        for (int i = 0; i < 12; i++)
        {
            insert(i, i * 10);
        }
        for (int i = 0; i < 5; i++)
        {
            extractMax();
        }
        priorityQueue pq2;
        for (int i = 10; i <= 20; i++)
        {
            pq2.insert(i, i * 10);
        }
        
        meld(*this, pq2);
        print();
        cout<<"extracting on melded tree"<<endl;
        extractMax();
        print();
        //new
         
        //
        // find_max();
        // Delete(190);
        // find_max();
        cout << "Successfully passed!" << endl;
    }

    void testFromFile(){
        freopen("input.txt", "r", stdin);
        //freopen("MyOutput.txt", "w", stdout);
        while(true){
            int n;
            cin>>n;
            if(n==0) {
                cout<<"Exiting..."<<endl;
                break;
            }
            if(n==1){
                int key, value;
                cin>>key>>value;
                insert(key, value);
            }
            else if(n==2){
                extractMax();
            }
            else if(n==3){
                int value, new_key;
                cin>>value>>new_key;
                increaseKey(value, new_key);
            }
            else if(n==4){
                int value;
                cin>>value;
                Delete(value);
            }
            else if(n==5){
                find_max();
            }
            else if(n==6){
                print();
            }
            else if(n==7){
                is_Empty();
            }
        }
    }
};

int main()
{
    priorityQueue pq;
    pq.make_heap();
    pq.test();
    //pq.testFromFile();
}
