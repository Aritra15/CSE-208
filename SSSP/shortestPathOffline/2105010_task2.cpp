#include<bits/stdc++.h>
using namespace std;

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


int main()
{
    int n,m;
    cin>>n>>m;

    vector<vector<int>>edges;

    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        vector<int> temp ={u-1,v-1,w};
        edges.push_back(temp);
    }

    int a,b;
    cin>>a>>b;

    int l,h;
    cin>>l>>h;

    int src,dest;
    cin>>src>>dest;

    int initialDistance = bellmanFord(edges,n,src-1,dest-1);

    int minVal,minWeight =initialDistance ;

    for(int i=l;i<=h;i++){
        vector<vector<int>>edges2 = edges;
        edges2.push_back({a-1,b-1,i});
        int dist = bellmanFord(edges2,n,src-1,dest-1);
        if(dist!=INT_MIN && dist<minWeight){
            minWeight = dist;
            minVal = i;
        }
    }

    if(minWeight<initialDistance){
        cout<<minVal<<" "<<minWeight<<endl;
    }
    else cout<<"impossible"<<endl;
    
}
