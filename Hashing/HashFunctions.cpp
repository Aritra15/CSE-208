#ifndef HASH_H
#define HASH_H
#include <bits/stdc++.h>
using namespace std;

bool isPrime(int n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

long long int findNextPrime(int &n)
{
    while (true)
    {
        if (isPrime(n))
            return n;
        n++;
    }
}

class hashFunctions
{
protected:
    long long int FNV_OFFSET_BASIS = 2166136261;
    long long int FNV_PRIME = 16777619;
    unsigned int fnv1a_hash(const std::string &s)
    {
        long long int hash = FNV_OFFSET_BASIS;
        for (char c : s)
        {
            hash ^= static_cast<unsigned int>(c);
            hash *= FNV_PRIME;
        }
        return hash;
    }
    
    long long int djb2_hash(const std::string &s)
    {
        unsigned int hash_value = 5381;
        for (char c : s)
        {
            hash_value = ((hash_value << 5) + hash_value) + static_cast<unsigned int>(c);
        }
        return hash_value;
    }

public:
    long long int hash1(string &s)
    {
        return fnv1a_hash(s);
    }
    long long int hash2(string &s)
    {
        return djb2_hash(s);
    }
    long long int auxHash(string &s)
    {
        long long int hash = 0;
        for (int i = 0; i < s.size(); i++)
        {
            hash += s[i];
        }
        return hash;
    }
    virtual bool insert(string key, int value) = 0;
    virtual void remove(string key) = 0;
    //virtual bool find(string key) = 0;
    // virtual void reHash(int flag) = 0;
};

#endif
