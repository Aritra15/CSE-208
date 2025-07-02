#include<bits/stdc++.h>
#include "separateChaining.cpp"
using namespace std;
int main()
{
    int n,l;
    cin>>n>>l;
    vector<string> sequences;
    SeparateChaining sc(1000,1,5);
    for(int i=0;i<n;i++){
        string s;
        cin>>s;
        sequences.push_back(s);
        string complement="";
        for(int i=0;i<l;i++){
            if(s[i]=='A'){complement.push_back('T');}
            if(s[i]=='T'){complement.push_back('A');}
            if(s[i]=='G'){complement.push_back('C');}
            if(s[i]=='C'){complement.push_back('G');}
        }
        reverse(complement.begin(),complement.end());
        int val;
        bool found = sc.find(complement,val);
        if(found){
            sc.insert(s,1);
        }else{
            sc.insert(s,0);
        }
    }
    for(int i=0;i<sequences.size();i++){
        int val=0;
        bool found = sc.find(sequences[i],val);
        string complement="";
        string s=sequences[i];
        for(int i=0;i<l;i++){
            if(s[i]=='A'){complement.push_back('T');}
            if(s[i]=='T'){complement.push_back('A');}
            if(s[i]=='G'){complement.push_back('C');}
            if(s[i]=='C'){complement.push_back('G');}
        }
        reverse(complement.begin(),complement.end());
        if(val){
            cout<<complement<<" ";
            cout<<sequences[i]<<endl;
        }
    }
}