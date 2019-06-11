#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
char a[5][5];
int n,MAX;

int judge(int row,int col){
    for(int i=row-1;i>=0;i--){
        if(a[i][col]=='@')return 1;
        if(a[i][col]=='X')break;
    }
    for(int i=col-1;i>=0;i--){
        if(a[row][i]=='@')return 1;
        if(a[row][i]=='X')break;
    }
    return 0;
}

void DFS(int pos,int count){
    int r,c;
    if(pos==n*n){
        if(MAX<count){
            MAX=count;
            return;
        }
    }
    else{
        r=pos/n;c=pos%n;
        if(a[r][c]=='.'&&judge(r,c)==0){
            a[r][c]='@';
            DFS(pos+1,count+1);
            a[r][c]='.';
        }
        DFS(pos+1,count);
    }
}


int main(){
    while(scanf("%d",&n)!=EOF&&n!=0){
        memset(a,0,sizeof(a));MAX=0;
        for(int i=0;i<n;i++)scanf("%s",&a[i]);
        DFS(0,0);
        printf("%d\n",MAX);
    }
    return 0;
}