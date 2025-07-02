#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> floydWarshall(vector<vector<int>>&cost)
{
    int n = cost.size();

    for(int k=0;k<n;k++)
    {
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(cost[i][k]!=INT_MAX && cost[k][j]!=INT_MAX)
                    cost[i][j] = min(cost[i][j],cost[i][k]+cost[k][j]);
            }
        }
    }
    // for(auto i:cost){
    //     for(auto j:i){
    //         cout<<j<<" ";
    //     }
    //     cout<<endl;
    // }
    return cost;
}

int main()
{
    int n,m;
    cin>>n>>m;
    vector<vector<int>>cost(n,vector<int>(n,INT_MAX));
    
    for(int i=0;i<n;i++){
        cost[i][i]=0;
    }
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        cost[u-1][v-1]=w;
        cost[v-1][u-1]=w;
    }
    // for(auto i:cost){
    //     for(auto j:i){
    //         cout<<j<<" ";
    //     }
    //     cout<<endl;
    // }
    int threshold;
    cin>>threshold;

    cost = floydWarshall(cost);

     for(auto i:cost){
        for(auto j:i){
            cout<<j<<" ";
        }
        cout<<endl;
    }

    int minimum=INT_MAX;
    for(int i=0;i<n;i++){
        int c = 0;
        for(int j=0;j<n;j++){
            if(cost[i][j]<=threshold && j!=i){
                c++;
            }
        }
        minimum = min(c,minimum);
    }
    //cout<<minimum<<endl;

    for(int i=0;i<n;i++){
        int c = 0;
        for(int j=0;j<n;j++){
            if(cost[i][j]<=threshold && j!=i){
                c++;
            }
        }
        if(c==minimum){
            cout<<i+1<<" ";
        }
    }
    
}