#include<bits/stdc++.h>
using namespace std;
int primsAlgorithm(vector<vector<pair<int,int>>>&adj,int n,int source){

    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    vector<int>visited(n,0);

    pq.push({0,source});
    int sum = 0;
    
    while(!pq.empty())
    {
        auto i=pq.top();
        pq.pop();
        int node = i.second;
        int weight = i.first;

        if(visited[node]==1)continue;

        visited[node] = 1;
        sum+=weight;

        for(auto it:adj[node]){
            int no = it.first;
            int w = it.second;
            if(visited[no]==0){
                pq.push({w,no});
            }
        }

    }
    return sum;

}
int main()
{
    //given a weight undirected graph.
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
    
    cout<<primsAlgorithm(adj,n,0);
}