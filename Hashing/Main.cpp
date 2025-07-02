#include <bits/stdc++.h>
#include "separateChaining.cpp"
#include "DoubleHashing.cpp"
#include "CustomHashing.cpp"
using namespace std;
string generateRandomWords(int length)
{
    string s = "";
    for (int i = 0; i < length; i++)
    {
        s += 'a' + rand() % 26;
    }
    return s;
}

void shuffle(vector<string> &strings)
{
    random_device rd;
    mt19937 g(rd());
    const int array_size = strings.size();
    shuffle(strings.begin(), strings.end(), g);
}
template<typename t>
class Map
{
private:
    SeparateChaining<t> sc;
    doubleHashing<t> dh;
    CustomHashing<t> ch;
    int collisionResolutionTechnique;

public:
    Map(int N, int hashFunction, int collisionResolutionTechnique, int c = 10)
    {
        if (collisionResolutionTechnique == 1)
        {
            sc = SeparateChaining<t>(N, hashFunction, c);
        }
        else if (collisionResolutionTechnique == 2)
        {
            dh = doubleHashing<t>(N, hashFunction);
        }
        else if (collisionResolutionTechnique == 3)
        {
            ch = CustomHashing<t>(N, hashFunction);
        }
        this->collisionResolutionTechnique = collisionResolutionTechnique;
    }

    bool insert(string key, int value)
    {
        if (collisionResolutionTechnique == 1)
        {
            return sc.insert(key, value);
        }
        else if (collisionResolutionTechnique == 2)
        {
            return dh.insert(key, value);
        }
        else if (collisionResolutionTechnique == 3)
        {
            return ch.insert(key, value);
        }
    }
    void remove(string key)
    {
        if (collisionResolutionTechnique == 1)
        {
            sc.remove(key);
        }
        else if (collisionResolutionTechnique == 2)
        {
            dh.remove(key);
        }
        else if (collisionResolutionTechnique == 3)
        {
            ch.remove(key);
        }
    }

    bool find(string key)
    {
        if (collisionResolutionTechnique == 1)
        {
            return sc.find(key);
        }
        else if (collisionResolutionTechnique == 2)
        {
            return dh.find(key);
        }
        else if (collisionResolutionTechnique == 3)
        {
            return ch.find(key);
        }
    }

    int getCollisions()
    {
        if (collisionResolutionTechnique == 1)
        {
            return sc.getCollisions();
        }
        else if (collisionResolutionTechnique == 2)
        {
            return dh.getCollisions();
        }
        else if (collisionResolutionTechnique == 3)
        {
            return ch.getCollisions();
        }
    }

    int getProbes()
    {
        if (collisionResolutionTechnique == 1)
        {
            return sc.getProbes();
        }
        else if (collisionResolutionTechnique == 2)
        {
            return dh.getProbes();
        }
        else if (collisionResolutionTechnique == 3)
        {
            return ch.getProbes();
        }
    }

    void setProbes(int probes)
    {
        if (collisionResolutionTechnique == 1)
        {
            sc.setProbes(probes);
        }
        else if (collisionResolutionTechnique == 2)
        {
            dh.setProbes(probes);
        }
        else if (collisionResolutionTechnique == 3)
        {
            ch.setProbes(probes);
        }
    }

    void print()
    {
        if (collisionResolutionTechnique == 1)
        {
            sc.print();
        }
        else if (collisionResolutionTechnique == 2)
        {
            dh.print();
        }
        else if (collisionResolutionTechnique == 3)
        {
            // ch.print();
        }
    }

    void reHash(bool flag)
    {
        if (collisionResolutionTechnique == 1)
        {
            sc.reHash(flag);
        }
        else if (collisionResolutionTechnique == 2)
        {
            dh.reHash(flag);
        }
        else if (collisionResolutionTechnique == 3)
        {
            ch.reHash(flag);
        }
    }

    int getNumberOfElements()
    {
        if (collisionResolutionTechnique == 1)
        {
            return sc.getNumberOfElements();
        }
        else if (collisionResolutionTechnique == 2)
        {
            return dh.getNumberOfElements();
        }
        else if (collisionResolutionTechnique == 3)
        {
            return ch.getNumberOfElements();
        }
    }
};

int main()
{
    float report[3][3][2][2];

    long long sizes[3] = {5000, 10000, 20000};

    vector<string> words;

    for (int i = 0; i < 10000; i++)
    {
        int n = rand() % 6 + 5;
        string s = generateRandomWords(n);
        while (find(words.begin(), words.end(), s) != words.end())
        {
            n = rand() % 6 + 5;
            s = generateRandomWords(n);
        }
        words.push_back(s);
    }

    // for(int i=0;i<10000;i++){
    //     cout<<words[i]<<endl;
    // }

    int chainlength = 10;

    for (int i = 0; i < 3; i++)
    {
        int cursize = sizes[i];
        for (int k = 0; k < 2; k++)
        {
            for (int j = 0; j < 3; j++)
            {
                Map<int> m(cursize, k + 1, j + 1, chainlength);
                vector<string> strings;
                for (int l = 0; l < 10000; l++)
                {
                    if (m.insert(words[l], l + 1))
                        strings.push_back(words[l]);
                }
                report[i][j][k][0] = m.getCollisions();
                shuffle(strings);
                m.setProbes(0);
                for (int l = 0; l < 1000; l++)
                {
                    m.find(strings[l]);
                }
                // shuffle(words);
                // m.setProbes(0);
                // for (int l = 0; l < 1000; l++)
                // {
                //     m.find(words[l]);
                // }
                report[i][j][k][1] = m.getProbes() / (float)1000;
            }
        }
    }
    freopen("output.txt", "w", stdout);
    cout << " " << setw(68) << setfill('_') << "" << endl;
    cout << setfill(' ');
    cout << "| Hash       | Collision         | Hash Function 1 | Hash Function 2 |" << endl;
    cout << "| Table Size | Resolution Method | Colls. | Probes | Colls. | Probes |" << endl;
    cout << "|" << setw(69) << setfill('_') << "|" << endl;
    cout << setfill(' ');
    long long i = 0;
    for (long long n : sizes)
    {
        cout << "| N = " << setw(7) << left << sizes[i];

        for (long long j = 0; j < 3; j++)
        {
            if (j == 0)
                cout << "| Separate Chaining | ";
            else if (j == 1)
                cout << "|" << setw(34) << right << "| Double Hashing    | ";
            else
                cout << "|" << setw(34) << right << "| Custom Probing    | ";

            for (long long k = 0; k < 2; k++)
            {
                for (long long m = 0; m < 2; m++)
                {
                    if (m == 0)
                        cout << defaultfloat << setw(5) << setprecision(5) << right << report[i][j][k][m] << "  ";
                    if (m == 1)
                        cout << fixed << setw(2) << setprecision(3) << " " << report[i][j][k][m] << "  ";
                }

                cout << "| ";
            }

            cout << endl;
        }

        cout << "|" << setw(69) << setfill('_') << "|" << endl;
        cout << setfill(' ');
        i++;
    }
}