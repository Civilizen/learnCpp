#include<iostream>
#include<cstdio>
using namespace std;
#define maxn 1005
#define maxm 30100
#define Max 1<<30
int t[maxn],s[maxn],dist[maxn];
int tot;
int n,k,m;
struct Edge{
    int start,end;
    int val;
}edge[maxm];

void addedge(int u,int v,int w){
    edge[tot].start=u;
    edge[tot].end=v;
    edge[tot++].val=w;
}

bool bellman()
{
	int flag;
	for (int k = 1; k <= n; k++) //  走n条边
	{
		flag = 0;
		for (int u = 0; u < tot; u++) // 按顺序对边集数组中的每条条边进行处理
			if (dist[edge[u].start] + edge[u].val < dist[edge[u].end])
			{
				dist[edge[u].end] = dist[edge[u].start] + edge[u].val;
				flag = 1;
			}
	}
	if (flag == 1)
		cout << "有负数环";
}

int main(){
	int a,b,c;
	while(scanf("%d%d%d",&n,&k,&m)!=EOF){
		tot=0;
		for(int i=1;i<=n;++i){
			scanf("%d",&t[i]);
		}
		for(int i=1;i<=k;++i){
			scanf("%d%d",&a,&b);
			addedge(b,a,-t[b]);
		}
		for(int i=1;i<=m;++i){
			scanf("%d%d%d",&a,&b,&c);
			addedge(b,a,t[a]+c);
		}
		for(int i=0;i<=n;++i){
			dist[i]=0;
		}
		if(bellman()){
			int tag=1,maxfinish,minfinish;
			maxfinish=minfinish=dist[1];
			for(int i=2;i<=n;i++){
				if(dist[i]>maxfinish)
					maxfinish=dist[i];
				else if(dist[i] < minfinish){
					minfinish = dist[i];
					tag = i;
				}
			}
			printf("%d\n", t[tag] + (maxfinish - minfinish));
		}
		else printf("No solutions!\n");
	}
}


/*
10 11 2
41
51
50
36
38
45
21
32
32
29
1 2
1 8
1 10
2 3
7 9
7 4
8 9
8 4
9 3
10 5
10 7
6 2 3
3 8 64

 */