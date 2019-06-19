#include<iostream>
#include<cstdio>
#include<stdlib.h>
#include<cstring>
#include<cmath>
using namespace std;

int n,Min,pos;
int count=1;
int point[202][2];
int dist[202];
int G[202][202];

int main(){

    while(scanf("%d",&n)!=EOF&&n){
        for(int i=0;i<n;++i){
            G[i][i]=0;
        }
        for(int i=0;i<n;++i){
            scanf("%d%d",&point[i][0],&point[i][1]);
        }
        for(int i=0;i<n-1;i++){
            for(int j=i+1;j<n;j++){
                G[i][j]=G[j][i]=((point[i][0] - point[j][0]) * (point[i][0] - point[j][0]) + (point[i][1] - point[j][1]) * (point[i][1] - point[j][1]));
            }
        }
        for(int i=0;i<n;i++){
            dist[i]=G[0][i];
        }
        G[0][0]=1;
        for(int i=0;i<n-1;i++){
            Min=1<<30;
            for(int k=0;k<n;++k){
                if(dist[k]<Min&&(G[k][k]!=1)){
                    pos=k;Min=dist[k];
                }
            }
            G[pos][pos]=1;
            for(int j=0;j<n;j++){
                if((G[j][j]!=1&&dist[j]>max(dist[pos],G[pos][j])))
                    dist[j]=max(dist[pos],G[pos][j]);
            }
        }

        printf("Scenario #%d\nFrog Distance = %0.3f\n\n",count++,sqrt(dist[1]));
    }
    return 0;
}