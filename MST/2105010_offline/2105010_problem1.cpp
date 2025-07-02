#include<bits/stdc++.h>
#include "kruskalsAlgorithm.cpp"
using namespace std;

int minWeight=0;

set<vector<pair<int, pair<int, int>>>> AllPrintedCombinations;

void printCurrentCombination(vector<pair<int, pair<int, int>>>& currentCombination) {
    //make sure all the edges are of form (u,v,w) where u<v.
    for (auto& edge : currentCombination) {
        if (edge.second.first > edge.second.second) {
            swap(edge.second.first, edge.second.second);
        }
    }
    // Sort the edges to ensure uniqueness in printing
    sort(currentCombination.begin(), currentCombination.end(),
         [](const auto& a, const auto& b) {
             // Compare based on the edges only
             return tie(a.second.first, a.second.second) < tie(b.second.first, b.second.second);
         });

    // check if the combination newly generated is unique or not.
    if (AllPrintedCombinations.count(currentCombination) == 0) {
        AllPrintedCombinations.insert(currentCombination);

        cout<<AllPrintedCombinations.size()<<".[";

     
        for(int i=0;i<currentCombination.size();i++)
        {
            cout<<"["<<currentCombination[i].second.first-1<<","<<currentCombination[i].second.second-1<<","<<currentCombination[i].first<<"]";
            if(i!=currentCombination.size()-1)
            {
                cout<<", ";
            }
        }
        cout << "]"<<endl;
        
    }
}


bool dfs(vector<vector<int>>&adj,vector<bool>&visited,int startNode)
{
    visited[startNode]=true;
    for(auto node:adj[startNode])
    {
        if(!visited[node])
        {
            dfs(adj,visited,node);
        }
    }
}

void dfsHelper(vector<pair<int,pair<int,int>>>currentCombination,int n)
{
    vector<bool>visited(n+1,false);
    vector<vector<int>>adj(n+1);
    for(auto edge:currentCombination)
    {
        adj[edge.second.first].push_back(edge.second.second);
        adj[edge.second.second].push_back(edge.second.first);
    }
    dfs(adj,visited,1);
    for(int i=1;i<=n;i++)
    {
        if(!visited[i])
        {
            return;
        }
    }
    printCurrentCombination(currentCombination);
}

void generateAllCombinations(vector<pair<int,pair<int,int>>>adj,vector<pair<int,pair<int,int>>>&currentCombination,int n,int index,int vertices)
{
    if(n==0)
    {
        
        int weight =0;
        for(auto edge:currentCombination)
        {
            weight+=edge.first;

        }
        if(weight==minWeight)
        {
            dfsHelper(currentCombination,vertices);
        }

        return;
    }
    for(int i=index;i<adj.size();i++)
    {
        currentCombination.push_back(adj[i]);
        generateAllCombinations(adj,currentCombination,n-1,i+1,vertices);
        currentCombination.pop_back();
    }
}


int main()
{
    int n,m;
    cin>>n>>m;
    vector<pair<int,pair<int,int>>>adj;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj.push_back({w,{u+1,v+1}});
        adj.push_back({w,{v+1,u+1}});
    }

    minWeight = minSpanningTree(adj,n);

    //cout<<minWeight<<endl;

    vector<pair<int,pair<int,int>>>currentCombination;

    cout<<"MSTs:\n";
    generateAllCombinations(adj,currentCombination,n-1,0,n);



}