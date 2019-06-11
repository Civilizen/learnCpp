#include<iostream>
#include<map>
#include<queue>
#include<string>
using namespace std;

map<string,string>M;
map<string,string>::iterator it;
string goal="12345678x";
queue<string>qu;

void Insert(string s1,int t1,int t2){
    char tem;
    string s2;
    s2=s1;
    tem=s2[t1];s2[t1]=s2[t2];s2[t2]=tem;
    it=M.find(s2);
    if(it==M.end()){
        M[s2]=s1;
        qu.push(s2);
    }
}

void Search(){
    string s1=goal;
    M[s1]=s1;
    qu.push(s1);
    int t1,t2;
    while (!qu.empty()){
        s1=qu.front();qu.pop();
        for(t1=0;t1<9;t1++)if(s1[t1]=='x')break;
        if(t1%3!=2){t2=t1+1;Insert(s1,t1,t2);}
        if(t1%3!=0){t2=t1-1;Insert(s1,t1,t2);}
        if(t1/3!=0){t2=t1-3;Insert(s1,t1,t2);}
        if(t1/3!=2){t2=t1+3;Insert(s1,t1,t2);}
    }

}


int main(){
    M.clear();
    Search();
    string s,s1;
    int t1,t2;
    char c;
    while(cin>>c){
        s="";s+=c;
        for(int i=1;i<9;i++){cin>>c;s+=c;}
        it=M.find(s);
        if(it==M.end())cout<<"unsolvable"<<endl;
        else{
            while(s!=goal){
                it=M.find(s);
                s1=it->second;
                for(t1=0;t1<9;++t1)if(s[t1]=='x')break;
                for(t2=0;t2<9;++t2)if(s1[t2]=='x')break;
                t1=t2-t1;
                if(t1==3)cout<<'d';
                else if(t1==1)cout<<'r';
                else if(t1==-1)cout<<'l';
                else if(t1==-3)cout<<'u';
                s=s1;
            }
            cout<<endl;
        }
    }
    return 0;
}