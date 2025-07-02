#include <bits/stdc++.h>
#include "kruskalsAlgorithm.cpp"
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<pair<int, pair<int, int>>> adj;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj.push_back({w, {u, v}});
    }

    vector<pair<int, pair<int, int>>> backUpGraph = adj;
    int minWeight = minSpanningTree(adj, n);

    // finding the critical edges by removing the edges and checking if that increases the weight of the new mst.
    vector<int> indicesOfPseudoCriticalEdges;

    cout << "Critical edges: [";
    int flag = 0;
    for (int i = 0; i < adj.size(); i++)
    {
        vector<pair<int, pair<int, int>>> adj2 = backUpGraph;
        adj2.erase(adj2.begin() + i);
       
        int weight = minSpanningTree(adj2, n);
        
        if (weight != minWeight)
        {
            cout << i;
            if (!flag)
                cout << ",";
            flag = 1;
        }
        else
        {
            // if it is not a critical edge then it is a candidate for being a pseudo critical edge,
            // so we include that edge forcefully in the mst to be formed and check if it can actually form an mst.
            int w = specialMinimumSpanningTree(adj2, n, backUpGraph[i]);
            if (w == minWeight)
            {
                indicesOfPseudoCriticalEdges.push_back(i);
            }
        }
    }
    cout << "]," << endl;

    cout << "Pseudo-critical edges: [";
    for (int i = 0; i < indicesOfPseudoCriticalEdges.size(); i++)
    {
        cout << indicesOfPseudoCriticalEdges[i];
        if (i != indicesOfPseudoCriticalEdges.size() - 1)
            cout << ",";
    }
    cout << "]" << endl;

 
}