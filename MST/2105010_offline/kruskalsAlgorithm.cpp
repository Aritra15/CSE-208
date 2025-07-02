#include<bits/stdc++.h>
#include "disjointSet.cpp"
using namespace std;

//return weight of edges of spanning tree
int minSpanningTree(vector<pair<int,pair<int,int>>>& edges, int n) { //tuple of form (w,u,v)
    int weight = 0;
    sort(edges.begin(), edges.end());
    DisjointSet ds(n+1);
    for (int i = 0; i < edges.size(); i++) {
        int wt = edges[i].first;
        int u = edges[i].second.first;
        int v = edges[i].second.second;
        int ulp_u = ds.findUltimateParent(u);
        int ulp_v = ds.findUltimateParent(v);
        if (ulp_u != ulp_v) {
            ds.UnionByRank(u, v);
            weight += wt;
        }
    }
    return weight;
}

//Here, we forcefully push the edge into the mst.
int specialMinimumSpanningTree(vector<pair<int, pair<int, int>>> &edges, int n, pair<int, pair<int, int>> edge) {
    int weight = 0;
    sort(edges.begin(), edges.end());
    DisjointSet ds(n + 1);
    ds.UnionByRank(edge.second.first, edge.second.second);
    weight += edge.first;
    for (int i = 0; i < edges.size(); i++) {
        int wt = edges[i].first;
        int u = edges[i].second.first;
        int v = edges[i].second.second;
        int ulp_u = ds.findUltimateParent(u);
        int ulp_v = ds.findUltimateParent(v);
        if (ulp_u != ulp_v) {
            ds.UnionByRank(u, v);
            weight += wt;
        }
    }
    return weight;
}

