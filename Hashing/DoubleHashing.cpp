#include <bits/stdc++.h>
#include "hashFunctions.cpp"
using namespace std;
template <typename t>
class doubleHashing : public hashFunctions
{
private:
    int N;
    int collisions;
    int probes;
    int numberOfElements;
    int hashFunction;
    vector<pair<string, int>> table;
    vector<int> isDeleted;

public:
    doubleHashing(int N = 0, int hashFunction = 0)
    {
        this->N = findNextPrime(N);
        table.clear();
        table.resize(this->N, {"", 0});
        isDeleted.clear();
        isDeleted.resize(this->N, 0);
        this->hashFunction = hashFunction;
        numberOfElements = 0;
        collisions = 0;
        probes = 0;
    }
    bool insert(string key, t value)
    {
        if (numberOfElements > 0.99 * N)
        {
            return false;
        }

        unsigned int index = hashFunction == 1 ? hash1(key) : hash2(key);
        index = index % N;

        int i = 1;

        if (table[index].first != "")
            collisions++;

        while (table[index].first != "" && table[index].first != key)
        {
            index = (index + i * auxHash(key)) % N;
            i++;
            probes++;
            // collisions++;
        }

        table[index] = {key, value};
        isDeleted[index] = 0;
        numberOfElements++;
        return true;
    }
    void remove(string key)
    {
        unsigned int index = hashFunction == 1 ? hash1(key) : hash2(key);
        index = index % N;
        int i = 1;
        while (table[index].first != key)
        {
            index = (index + i * auxHash(key)) % N;
            i++;
            probes++;
            if(table[index].first=="" && isDeleted[index] == 0) return;
        }
        table[index].first = "";
        isDeleted[index] = 1;
        numberOfElements--;
    }
    bool find(string key)
    {
        unsigned int index = hashFunction == 1 ? hash1(key) : hash2(key);
        index = index % N;
        int i = 1;
        probes++;

        while (table[index].first != key)
        {
            index = (index + i * auxHash(key)) % N;
            i++;
            probes++;
            if (table[index].first == "" && isDeleted[index] == 0)
            {
                return false;
            }
        }
        if (table[index].first == key)
        {
            return true;
        }
    }

    void print()
    {
        for (int i = 0; i < N; i++)
        {
            cout << i << " " << table[i].first << " " << table[i].second << endl;
        }
    }
    int getCollisions()
    {
        return collisions;
    }
    int getProbes()
    {
        return probes;
    }
    void setProbes(int probes)
    {
        this->probes = probes;
    }
    int getNumberOfElements()
    {
        return numberOfElements;
    }

    void reHash(bool flag)
    {
        // int newN = flag == 1 ? 2*N : N/2;
        // newN = findNextPrime(newN);
        // int newCollisions = 0;
        // vector<pair<string,int>> newTable;
        // vector<int> newIsDeleted;
        // newTable.clear();
        // newTable.resize(newN,{"",0});
        // newIsDeleted.clear();
        // newIsDeleted.resize(newN,0);
        // for(int i = 0;i<N;i++){
        //     if(table[i].first != ""){
        //         unsigned int index = hashFunction == 1 ? hash1(table[i].first) : hash2(table[i].first);
        //         index = index % newN;
        //         int j = 1;
        //         while(newTable[index].first != ""){
        //             index = (index + j*auxHash(table[i].first))%newN;
        //             j++;
        //             newCollisions++;
        //         }
        //         newTable[index] = table[i];
        //         newIsDeleted[index] = 0;
        //     }
        // }
        // table = newTable;
        // isDeleted = newIsDeleted;
        // N = newN;
        // collisions = newCollisions;
    }
};