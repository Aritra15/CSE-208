#include<bits/stdc++.h>
#include "fordFulkerson.cpp"
using namespace std;

void findMinCutVertices(vector<vector<int>>&rGraph,int s,int t){
    
    int maxFlow = fordFulkerson(rGraph,s,t);

    int n=rGraph.size();
    vector<int>visited(n,0);
    vector<int>parent(n,-1);

    bfs(rGraph,s,t,parent,visited);

    // for(auto i:visited)cout<<i<<" ";
    // cout<<endl;

    vector<int>sourceCut,sinkCut;

    for(int i=0;i<n;i++){
        if(visited[i]){
            sourceCut.push_back(i+1);
        }
        else 
            sinkCut.push_back(i+1);
    }

    cout<<"[";
    cout<<"{";
    for(int i=0;i<sourceCut.size();i++){
        cout<<sourceCut[i];
        if(i!=sourceCut.size()-1){
            cout<<", ";
        }
    }
    cout<<"}, ";
    cout<<"{";
    for(int i=0;i<sinkCut.size();i++){
        cout<<sinkCut[i];
        if(i!=sinkCut.size()-1){
            cout<<", ";
        }
    }
    cout<<"}";
    cout<<"]"<<endl;

    cout<<maxFlow<<endl;
}

int main()
{
    int n,m;
    cin>>n>>m;

    vector<vector<int>>graph(n,vector<int>(n));

    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        graph[u-1][v-1]=w;
    }

    int source,sink;
    cin>>source>>sink;

    source = source-1;
    sink = sink-1;

    findMinCutVertices(graph,source,sink);

    


}