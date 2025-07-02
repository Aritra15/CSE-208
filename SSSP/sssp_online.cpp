#include<bits/stdc++.h>
using namespace std;
vector<int> shortestPaths(int n, vector<vector<int> >adj,int source,vector<int>tax,int dest)
{
    vector<int>distances(n,INT_MAX);
    
    priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >pq;
    distances[source] = 0;
    
    pq.push(make_pair(0,source));

    while(!pq.empty())
    {
        int dist = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        
        for(int i=0;i<adj[node].size();i++)
        {
            int vertex =adj[node][i];
            
            if(distances[node]!=INT_MAX &&  distances[node]+tax[node]<distances[vertex]){
                distances[vertex]=distances[node]+tax[vertex];
                pq.push(make_pair(distances[vertex],vertex));
            }
        }
    }
    cout<<distances[dest]<<endl;
    
    return distances;
}
int main()
{
    int n,m;
    cin>>n>>m;
    vector<int>tax(n);
    for(int i=0;i<n;i++)cin>>tax[i];
    vector<vector<int> >adj(n);
    for(int i=0;i<m;i++){
        int u,v;cin>>u>>v;
        adj[u-1].push_back(v-1);
        adj[v-1].push_back(u-1);
    }
    shortestPaths(n,adj,0,tax,n-1);
}