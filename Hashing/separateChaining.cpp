#include <bits/stdc++.h>
#include "hashFunctions.cpp"
using namespace std;

class SeparateChaining : public hashFunctions
{
private:
    int N;
    int originalN;
    int collisions;
    int probes;
    int numberOfElements;
    int hashFunction;
    int maximumChainLength;
    int c; // stores maximum allowed chain length
    vector<list<pair<string, int>>> table;
    vector<string> insertedKeys;
    int totalInsertionCount;
    int totalDeletionCount;

public:
    SeparateChaining(int N = 0, int hashFunction = 1, int c = 10)
    {
        this->N = findNextPrime(N);
        originalN = this->N;
        table.clear();
        table.resize(this->N);
        this->hashFunction = hashFunction;
        numberOfElements = 0;
        maximumChainLength = 0;
        collisions = 0;
        this->c = c;
        probes = 0;
        totalInsertionCount = 0;
        totalDeletionCount = 0;
    }

    void setC(int c)
    {
        this->c = c;
    }

    bool insert(string key, int value)
    {
        unsigned int index = hashFunction == 1 ? hash1(key) : hash2(key);
        index = index % N;

        collisions += (table[index].size() == 0) ? 0 : 1;
        probes += table[index].size();

        table[index].push_back({key, value});
        insertedKeys.push_back(key);

        numberOfElements++;
        totalInsertionCount++;

        if (table[index].size() > maximumChainLength)
        {
            maximumChainLength = table[index].size();
        }
        if (totalInsertionCount != 0 && totalInsertionCount % 100 == 0)
        {
            if (isChainLengthGreaterThanC())
            {
                reHash(1);
            }
        }
        return true;
    }
    void remove(string key)
    {
        unsigned int index = hashFunction == 1 ? hash1(key) : hash2(key);
        index = index % N;
        for (auto it = table[index].begin(); it != table[index].end(); it++)
        {
            if (it->first == key)
            {
                table[index].erase(it);
                break;
            }
            probes++;
        }
        numberOfElements--;
        totalDeletionCount++;
        // update maximum chain length
        for (auto i : table)
        {
            if (i.size() > maximumChainLength)
            {
                maximumChainLength = i.size();
            }
        }
        // rehash if maximum chain length is 80% of c
        if (totalDeletionCount != 0 && totalDeletionCount % 100 == 0 && N / 2 >= originalN)
        {
            if (isMaxChainLength80PercentOfC())
            {
                reHash(0);
            }
        }
    }
    bool find(string key,int &value)
    {
        unsigned int index = hashFunction == 1 ? hash1(key) : hash2(key);
        index = index % N;
        for (auto i : table[index])
        {
            probes++;
            if (i.first == key)
            {
                value = i.second;
                return true;
            }
            // probes++;
        }
        return false;
    }
    void reHash(bool flag)
    {

        cout << "Before rehashing..." << endl;
        printInformation();

        int newN = flag == 1 ? 2 * N : N / 2;
        newN = findNextPrime(newN);
        int newMaxChainLength = 0;
        int newCollisions = 0;
        vector<list<pair<string, int>>> newTable;
        newTable.clear();
        newTable.resize(newN);

        for (int i = 0; i < N; i++)
        {
            for (auto j : table[i])
            {
                unsigned int index = hashFunction == 1 ? hash1(j.first) : hash2(j.first);
                index = index % newN;
                newCollisions += newTable[index].size() != 0;
                newTable[index].push_back(j);
                if (newTable[index].size() > newMaxChainLength)
                {
                    newMaxChainLength = newTable[index].size();
                }
            }
        }

        table = newTable;
        N = newN;
        maximumChainLength = newMaxChainLength;
        collisions = newCollisions;

        cout << "After rehashing..." << endl;
        printInformation();
        cout << endl
             << endl;
    }
    bool isChainLengthGreaterThanC()
    {
        return maximumChainLength > c;
    }
    bool isMaxChainLength80PercentOfC()
    {
        return maximumChainLength > 0.8 * c;
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

    void print()
    {
        for (int i = 0; i < N; i++)
        {
            cout << i << " ";
            for (auto j : table[i])
            {
                cout << j.first << " ";
            }
            cout << endl;
        }
    }

    int getNumberOfElements()
    {
        return numberOfElements;
    }

    void printInformation()
    {
        // print avg probe searching 10% of the elements
        int noOfSearches = numberOfElements / 10;
        probes = 0;
        random_device rd;
        mt19937 g(rd());
        shuffle(insertedKeys.begin(), insertedKeys.end(), g);
        for (int i = 0; i < noOfSearches; i++)
        {
            int val;
            find(insertedKeys[i],val);
        }
        cout << "Avg Probes: " << probes / (float)noOfSearches << endl;
        cout << "Load Factor: " << numberOfElements / (float)N << endl;
        cout << "Maximum Chain Length: " << maximumChainLength << endl;
    }
};