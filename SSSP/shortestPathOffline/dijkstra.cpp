#include<bits/stdc++.h>
using namespace std;

// adj list will contain the adjacent nodes of vertices along with their weights
vector<int> shortestPaths(int n, vector<vector<pair<int,int>>>adj,int source)
{
    vector<int>distances(n,INT_MAX);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    distances[source] = 0;
    pq.push({0,source});

    while(!pq.empty())
    {
        int dist = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        for(auto edge: adj[node])
        {
            int vertex =edge.first;
            int edgeWeight = edge.second;
            
            if(distances[node]+edgeWeight<distances[vertex]){
                distances[vertex] = distances[node]+edgeWeight;
                pq.push({distances[vertex],vertex});
            }
        }
    }
    return distances;
}

int main()
{
    int n,m;
    cin>>n>>m;

    vector<vector<pair<int,int>>>adj(n);

    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    vector<int> dist= shortestPaths(n,adj,0);

    for(auto i:dist){
        cout<<i<<" ";
    }
}