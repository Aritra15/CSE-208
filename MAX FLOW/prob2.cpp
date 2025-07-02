#include<bits/stdc++.h>
#include "fordFulkerson.cpp"
using namespace std;
int main()
{
    int n,m;
    cin>>m>>n;

    vector<vector<int>>graph(2+m+n,vector<int>(2+m+n,0));

    map<int,vector<int>>vertexToData;

    for(int i=1;i<=m;i++){
        int height,age,status;
        cin>>height>>age>>status;

        vector<int>data={height,age,status};

        vertexToData[i]=data;
    }

    for(int i=m+1;i<=m+n;i++){
        int height,age,status;
        cin>>height>>age>>status;

        vector<int>data={height,age,status};

        vertexToData[i]=data;

        for(int j=1;j<=m;j++){
            vector<int>manData = vertexToData[j];
            int heightDiff=abs(manData[0]-height);
            int ageDiff = abs(manData[1]-age);
            int statusMatch=(manData[2]==status);
            if(heightDiff<=10 && ageDiff<=5 && statusMatch){
                graph[j][i]=1;
            }
        }
    }

    for(int i=1;i<=m;i++){
        graph[0][i]=1;
    }

    for(int i=m+1;i<=m+n;i++){
        graph[i][m+n+1]=1;
    }

    cout<<fordFulkerson(graph,0,m+n+1)<<endl;
}