#include<bits/stdc++.h>
#include "kruskalsAlgorithm.cpp"
using namespace std;
int main()
{
    int n,m;
    cin>>n>>m;
    vector<pair<int, pair<int, int>>> adj;
    for(int i=1;i<=n;i++)
    {
        int u;
        cin>>u;
        adj.push_back({u,{i,n+1}});
    }
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        adj.push_back({w,{u,v}});
        adj.push_back({w,{v,u}});
    }
    int minweight= minSpanningTree(adj,n+1);
    cout<<minweight<<endl;
}