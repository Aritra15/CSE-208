#include<bits/stdc++.h>
#include "kruskalsAlgorithm.cpp"
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, pair<int, int>>> edges;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({w, {u, v}});
    }

    vector<pair<int, pair<int, int>>> backUpGraph = edges;
    int minWeight = minSpanningTree(edges, n);

    for (int i = 0; i < edges.size(); i++) {
        vector<pair<int, pair<int, int>>> new_edges = backUpGraph;
        new_edges.erase(new_edges.begin() + i);

        int weight = minSpanningTree(new_edges, n);

        if (weight != minWeight) {
            cout << "any" << endl;
        } else {
            int w = specialMinimumSpanningTree(new_edges, n, backUpGraph[i]);
            if (w == minWeight) {
                cout << "at least one" << endl;
            } else {
                cout << "none" << endl;
            }
        }
    }
}
