#include<bits/stdc++.h>
using namespace std;

int  bellmanFord(vector<vector<int>>&edges,int n,int source,int destination)
{
    vector<int>dist(n,INT_MAX);

    dist[source] = 0;

    for(int i=0;i<n-1;i++)
    {
        for(auto j:edges){
            int u = j[0];
            int v = j[1];
            int weight = j[2];
            if(dist[u]!= INT_MAX && dist[u]+weight<dist[v]){
                dist[v] = dist[u] + weight;
            }
        }
    }

    for(auto j:edges){
            int u = j[0];
            int v = j[1];
            int weight = j[2];
            if(dist[u]!= INT_MAX && dist[u]+weight<dist[v]){
                return INT_MIN;
            }
    }

    return dist[destination];
    
}

vector<int> bellmanFord2(vector<vector<int>>&edges,int source,int n)
{
    vector<int>dist(n,INT_MAX);

    dist[source] = 0;

    for(int i=0;i<n-1;i++)
    {
        for(auto j:edges){
            int u = j[0];
            int v = j[1];
            int weight = j[2];
            if(dist[u]!= INT_MAX && dist[u]+weight<dist[v]){
                dist[v] = dist[u] + weight;
            }
        }
    }

    for(auto j:edges){
            int u = j[0];
            int v = j[1];
            int weight = j[2];
            if(dist[u]!= INT_MAX && dist[u]+weight<dist[v]){
                return {-1};
            }
    }

    return dist;
    
}
