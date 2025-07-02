#include<bits/stdc++.h>
using namespace std;

int findMinCost(vector<int>&fuelCosts,vector<vector<pair<int,int>>>&adj,int src,int dest,int capacity)
{
    int n = fuelCosts.size();
    vector<vector<int>>cost(n,vector<int>(capacity+1,INT_MAX));
    priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>>pq;

    cost[src][0] = 0;
    pq.push({0,{src,0}});

    while(!pq.empty())
    {
        int u = pq.top().second.first;
        int fuel = pq.top().second.second;
        int costUntilNow = pq.top().first;
        pq.pop();

        //we stay at current place and refill 1 liter fuel
        if(fuel+1<=capacity && cost[u][fuel+1]>costUntilNow+fuelCosts[u])
        {
            cost[u][fuel+1] = costUntilNow+fuelCosts[u];
            pq.push({cost[u][fuel+1],{u,fuel+1}});
        }
        
        //we try to go to adjacent vertices if we have enough fuel.
        for(auto v:adj[u])
        {
            int v1 = v.first;
            int w = v.second;

            if(fuel>=w && cost[v1][fuel-w]>costUntilNow){
                cost[v1][fuel-w] = costUntilNow;
                pq.push({cost[v1][fuel-w],{v1,fuel-w}});
            }
        }
    }
    //print cost array
    // for(auto i:cost)
    // {
    //     for(auto j:i)
    //     {
    //         cout<<j<<" ";
    //     }
    //     cout<<endl;
    // }
    return cost[dest][0];
    
}

int main()
{
    int n,m,capacity;
    cin>>n>>m>>capacity;

    vector<int>fuelCosts(n);
    for(int i=0;i<n;i++) cin>>fuelCosts[i];

    vector<vector<pair<int,int>>>adj(n);

    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        adj[u-1].push_back({v-1,w});
        adj[v-1].push_back({u-1,w});
    }

    int src,dest;
    cin>>src>>dest;

    int cost = findMinCost(fuelCosts,adj,src-1,dest-1,capacity);

    cost==INT_MAX?cout<<"impossible\n":cout<<cost<<endl;

}
/*
5 5 10
1 10 2 12 13
1 2 9
1 3 8
2 3 1
2 4 1
3 4 7
1 4

4 5 9
5 3 6 2
1 2 1
2 3 3
1 3 5
3 4 1
1 4 6
1 4
*/