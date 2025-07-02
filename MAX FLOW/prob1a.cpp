#include<bits/stdc++.h>
using namespace std;

bool bfs(vector<vector<int>>&graph,int s,int t,vector<int>&parent,vector<int> &visited){
    int n=graph.size();
    fill(visited.begin(),visited.end(),0);
    fill(parent.begin(),parent.end(),-1);

    queue<int>q;
    q.push(s);
    parent[s]=-1;
    visited[s]=true;

    while(!q.empty()){
        int node = q.front();
        q.pop();

        for(int i=0;i<n;i++){
            if(!visited[i] && graph[node][i]>0){
                visited[i] = true;
                parent[i] = node;
                q.push(i);
            }
        }
    }
    //if the bfs is successful then the sink will be visited.
    return visited[t];
}

void fordFulkerson(vector<vector<int>>&rGraph,int s,int t){

    int n=rGraph.size();
    vector<int>visited(n,false);
    vector<int>parent(n,-1);
    int maxFlow=0;

    vector<vector<int>>netFlowGraph(n,vector<int>(n,0));

    while(bfs(rGraph,s,t,parent,visited)){
        int v = t;
        int currentFlow=INT_MAX;
        //finding the edge with minimum flow
        while(v!=s){
            currentFlow = min(currentFlow,rGraph[parent[v]][v]);
            v = parent[v];
        }

        maxFlow += currentFlow;

        //creating the residual graph again
        v=t;
        while(v!=s){
            rGraph[parent[v]][v] -=currentFlow;
            rGraph[v][parent[v]] +=currentFlow;
            netFlowGraph[parent[v]][v] +=currentFlow;
            v = parent[v];
        }
    } 

    int node = -1, maxFlowValue=0;
    for(int i=0;i<n;i++){
        int sum = 0;
        
        if(i == s || i==t)continue;

        for(int j=0;j<n;j++){
            sum+=netFlowGraph[i][j];
        }
        if(sum>maxFlowValue){
            maxFlowValue = sum;
            node = i+1;
        }
    }

    cout<<node<<" "<<maxFlowValue<<endl;

    //rough
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<netFlowGraph[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    
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

    fordFulkerson(graph,source,sink);
}