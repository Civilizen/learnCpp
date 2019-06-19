#include<iostream>
#include<cstdio>
using namespace std;
#define maxn 1005
#define maxm 30100
#define Max 1<<30
int c[maxn],s[maxn],dist[maxn];
int tot;
int n,m;

struct Edge{
    int start,end;
    int val;
}edge[maxm];

void addedge(int u,int v,int w){
    edge[tot].start=u;
    edge[tot].end=v;
    edge[tot++].val=w;
}

bool bellman(){
    int i,j;
    for(i=0;i<n;i++) dist[i]=Max;
    dist[0]=0;
    for(i=0;i<n;i++){
        for(j=0;j<tot;j++)
            if(dist[edge[j].start]+edge[j].val<dist[edge[j].end]){
                dist[edge[j].end]=dist[edge[j].start]+edge[j].val;
            }
    }
    for(int j=0;j<tot;j++)
        if(dist[edge[j].start]+edge[j].val<dist[edge[j].end])
            return 0;
    return 1;
}

int main(){
    int i,j,k;
    while(scanf("%d%d",&n,&m)!=EOF){
        tot=0;
        for(i=1;i<=n;++i){
            scanf("%d",&c[i]);
            addedge(i-1,i,c[i]);
            addedge(i,i-1,0);
            s[i]=s[i-1]+c[i];
        }
        while(m--){
            scanf("%d%d%d",&i,&j,&k);
            addedge(j,i-1,-k);
        }
        if(!bellman())printf("Bad Estimations\n");
        else printf("%d\n",dist[n]-dist[0]);
    }
    return 0;
}