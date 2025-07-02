#include<bits/stdc++.h>
#include "RedBlackTree.cpp"

using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    RedBlackTree<int> rbt;

    string s;

    while(cin >> s)
    {
        if(s =="I"){
            int key;
            string value;
            cin >> key >> value;
            rbt.Insert(key, value);
            rbt.print();
        }
        else if (s=="E"){
            int key;
            cin >> key;
            //cout<<"here"<<key<<endl;
            if(rbt.find(key)){
                rbt.erase(key);
                rbt.print();
            }   
            else{
                cout<< key<<" not found"<<endl;
            }
            
        }
        else if (s=="F"){
            int key;
            string value;
            cin >> key;
            if(cin.peek()=='\n'){
                if(rbt.find(key)){
                    cout<< key<<" found"<<endl;
                }else{
                    cout<< key<<" not found"<<endl;
                }
            }
            else{
                cin>>value;
                if(rbt.find(key,value)){
                    cout<< key<<" found"<<endl;
                }else{
                    cout<< key<<" not found"<<endl;
                }
            }
            
            //rbt.print();
        }
        else if (s=="Em"){
            if(rbt.Empty()){
                cout<<"yes"<<endl;
            }else{
                cout<<"no"<<endl;
            }
        }
        else if(s=="Clr"){
            if(rbt.Empty()){
                cout<<"unsucessful"<<endl;
            }else{
                rbt.clear();
                cout<<"sucessful"<<endl;
            }
        }else if(s=="S"){
            cout<<rbt.size()<<endl;
        }else if(s=="Itr"){
            rbt.Iteration();
        }
        
     }
    
    
}