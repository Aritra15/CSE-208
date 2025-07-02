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

int fordFulkerson(vector<vector<int>>&rGraph,int s,int t){

    int n=rGraph.size();
    vector<int>visited(n,false);
    vector<int>parent(n,-1);
    int maxFlow=0;

    while(bfs(rGraph,s,t,parent,visited)){
        int v = t;
        int currentFlow=INT_MAX;
        //finding the edge with minimum flow
        while(v!=s){
            currentFlow = min(currentFlow,rGraph[parent[v]][v]);
            v = parent[v];
        }

        maxFlow += currentFlow;
        //cout<<currentFlow<<endl;

        //creating the residual graph again
        v=t;
        while(v!=s){
            rGraph[parent[v]][v] -=currentFlow;
            rGraph[v][parent[v]] +=currentFlow;
            v = parent[v];
        }
    } 

    return maxFlow;
}
