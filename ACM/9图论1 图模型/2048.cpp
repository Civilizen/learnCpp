#include<iostream>
#include<queue>
#include<math.h>
#include<stdio.h>
#include<string.h>
using namespace std;
#define M 751
int p[M][2];
double dis[M][M];
int m,n;
int parent[M];

struct EdgeNode
{
  int start, end;
  double cost;
} edge, result[M];

bool operator<(const EdgeNode &a, const EdgeNode &b){
  if (a.cost > b.cost)
    return true;
  else
    return false;
}

priority_queue<EdgeNode> PQ;

void Change(){
  int i,j;
  for(i=1;i<=n;i++)
    for(j=i+1;j<=n;j++)
      if(dis[i][j]<=32766){
        edge.start=i;
        edge.end=j;
        edge.cost=dis[i][j];
        PQ.push(edge);
      }
}

int SetFind(int i){
  int r;
  for(r=i;parent[r]>0;r=parent[r]);
  while(i!=r){
    int s=parent[i];
    parent[i]=r;
    i=s;
  }
  return r;
}

void SetUnion(int i,int j){
  int temp=parent[i]+parent[j];
  if(parent[j]<parent[i]){parent[i]=j;parent[j]=temp;}
  else{parent[j]=i;parent[i]=temp;}
}

void Makedis(){
  int i, j;
  double r;
  for (i = 1; i <= n; ++i)
    for (j = i+1; j <= n; j++)
    {
      r = ((p[i][0] - p[j][0]) * (p[i][0] - p[j][0]) + (p[i][1] - p[j][1]) * (p[i][1] - p[j][1]));
      dis[i][j] = r;
    }
}

int main(){
  int i,k,p1,p2,pos1,pos2;
  int choose;
  int flag=1;
  scanf("%d",&k);
  while(k--){
    scanf("%d",&n);
    choose=0;
    memset(parent,-1,sizeof(parent));
    for(i=1;i<=n;i++){
      scanf("%d%d",&p[i][0],&p[i][1]);
    }
    Makedis();
    scanf("%d",&m);
    for(i=1;i<=m;i++){
      scanf("%d%d",&p1,&p2);
      dis[p1][p2]=dis[p2][p1]=32767;
      pos1=SetFind(p1);
      pos2=SetFind(p2);
      if(pos1!=pos2){SetUnion(pos1,pos2);choose++;}
    }
    Change();
    while(choose<n-1){
      edge=PQ.top();PQ.pop();
      pos1=SetFind(edge.start);
      pos2=SetFind(edge.end);
      if(pos1!=pos2){
        SetUnion(pos1,pos2);
        printf("%d %d\n",edge.start,edge.end);
        flag=0;
        choose++;
      }
    }
    if(flag==1)printf("\n");
    flag=1;
  }
  system("pause");
  return 0;
}

