#include<iostream>
#include<stdio.h>
using namespace std;

struct node{
    int val,num;
}p[10];
int n,m,count,k=0;

void DFS(const int& i){
    if(n==0){count++;return;}
    if(n<0)return;
    if(i==m)return;
    if(p[i].num){
        n-=p[i].val;
        --p[i].num;
        DFS(i);
        ++p[i].num;
        n+=p[i].val;
    }
    DFS(i+1);
}
int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        if(k++)printf("\n");
        for(int i=0;i<m;++i){
            scanf("%d%d",&p[i].val,&p[i].num);
        }
        count=0;
        DFS(0);
        printf("%d\n",count);
    }
    return 0;
}