#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define min(a, b) (((a) < (b)) ? (a) : (b))
int x,y,n,count=1;
int map[21][21];

void cal(){
    int i,j,k;
    for(k=1;k<=20;k++)
        for(i=1;i<=20;i++)
            for(j=1;j<=20;j++)
                map[i][j]=min(map[i][j],map[i][k]+map[k][j]);
}

int main(){
    while(scanf("%d",&x)!=EOF){
        memset(map,21,sizeof(map));
        for(int i=1;i<21;++i)map[i][i]=0;
        for(int i=1;i<20;++i){
            if(i!=1)scanf("%d",&x);
            for(int j=1;j<=x;j++){
                scanf("%d",&y);
                map[i][y]=map[y][i]=1;
            }
        }
        cal();
        scanf("%d",&n);
        printf("Test Set #%d\n",count++);
        for(int i=0;i<n;++i){
            scanf("%d%d",&x,&y);
            printf("%d to %d: %d\n",x,y,map[x][y]);
        }
        printf("\n");
    }
}