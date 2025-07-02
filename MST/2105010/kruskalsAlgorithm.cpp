#include<bits/stdc++.h>
#include "disjointSet.cpp"
using namespace std;

//return weight of edges of spanning tree
int minSpanningTree(vector<pair<int,pair<int,int>>>&adj,int n) //tuple of weight,u,v and n is the number of vertices(1 based indexing)
{
    int weight =0;
    sort(adj.begin(),adj.end());
    DisjointSet ds(n+1);
    for(int i=0;i<adj.size();i++)
    {
        int wt = adj[i].first;
        int u = adj[i].second.first;
        int v = adj[i].second.second;
        int ulp_u = ds.findUltimateParent(u);
        int ulp_v = ds.findUltimateParent(v);
        if(ulp_u!=ulp_v){
            ds.UnionByRank(u,v);
            weight+=wt;
        }
    }
    return weight;
}

int specialMinimumSpanningTree(vector<pair<int, pair<int, int>>> &adj2, int n, pair<int, pair<int, int>> edge)
{
    int weight = 0;
    sort(adj2.begin(), adj2.end());
    DisjointSet ds(n + 1);
    ds.UnionByRank(edge.second.first, edge.second.second);
    weight += edge.first;
    for (int i = 0; i < adj2.size(); i++)
    {
        int wt = adj2[i].first;
        int u = adj2[i].second.first;
        int v = adj2[i].second.second;
        int ulp_u = ds.findUltimateParent(u);
        int ulp_v = ds.findUltimateParent(v);
        if (ulp_u != ulp_v)
        {
            ds.UnionByRank(u, v);
            weight += wt;
        }
    }
    return weight;
}
