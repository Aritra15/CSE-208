#include<bits/stdc++.h>
using namespace std;
void floydWarshall(vector<vector<int>>&cost,vector<vector<int>>&next,int n)
{
    //vector<vector<int>>next(n,vector<int>(n));
    for(int k=0;k<n;k++)
    {
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)
            {
                if(cost[i][k]==INT_MAX || cost[k][j]==INT_MAX)
                    continue;
                if(cost[i][j]>cost[i][k]+cost[k][j]){
                    cost[i][j]=cost[i][k]+cost[k][j];
                    next[i][j]=next[i][k];
                }
            }
        }
    }

}
void printPath(vector<vector<int>>next,int src,int dest){
    
    while(src!=dest){
        cout<<src+1<<"->";
        src=next[src][dest];
    }
    cout<<dest+1;
}
int main()
{
    int n,m;
    cin>>n>>m;
    vector<vector<int>>adj(n,vector<int>(n,INT_MAX));
    vector<vector<int>>next(n,vector<int>(n));
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u-1][v-1]=w;
        adj[v-1][u-1]=w;
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(adj[i][j]==-1)
                next[i][j]=-1;
            else 
                next[i][j]=j;   
        }
    }
    floydWarshall(adj,next,n);
    int w1,w2;
    cin>>w1>>w2;
    w1--;
    w2--;
    int s=1,d=1;

    while(true){
        cin>>s>>d;
        if(s==-1 && d==-1){
            break;
        }
        s--;d--;
        int d1=INT_MAX;
        int d2=d1;
        if(!(adj[s][w1]==INT_MAX ||adj[w2][d]==INT_MAX)){
            d1=adj[s][w1]+adj[w2][d];
        }
        if(!(adj[s][w2]==INT_MAX ||adj[w1][d]==INT_MAX)){
            d2=adj[s][w2]+adj[w1][d];
        }
        if(d1==INT_MAX && d2==INT_MAX){
            cout<<"no path through wall"<<endl;
        }
        else if(d1<d2){
            cout<<"Path: ";
            printPath(next,s,w1);
            cout<<"->";
            printPath(next,w2,d);
            cout<<endl;
        }
        else{
            cout<<"Path: ";
            printPath(next,s,w2);
            cout<<"->";
            printPath(next,w1,d);
            cout<<endl;
        }

    }
}