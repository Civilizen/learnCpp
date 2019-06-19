#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define maxn 105
bool map[maxn][maxn];//输入的原始地图
bool amap[maxn][maxn];//邻接矩阵
int nmap[maxn][maxn];//记录产生的每个点的编号
int pre[maxn];
bool visited[maxn];
int pos[4][2]={{0,-1},{0,1},{-1,0},{1,0}};//变化方向
int n,m,k,x,y,count,num;

void createmap(int i,int j){
    //产生邻接矩阵
    int a=0,b=0;
    for(int t=0;t<4;++t){
        a=i+pos[t][0];
        b=j+pos[t][1];
        if(a >= 1 && a <= n&&b >= 1 && b <= m){
            if(!map[a][b]){
                amap[nmap[i][j]][nmap[a][b]]=1;
                amap[nmap[a][b]][nmap[i][j]]=1;
            }
        }
    }
}

bool dfs(int start){
    for(int i=1;i<count;++i){
        if(amap[start][i]==1&&visited[i]==0){
            visited[i]=1;
            if(pre[i]==-1||dfs(pre[i])){
                pre[i]=start;
                return 1;
            }
        }
    }
    return false;
}

int main(){
    while(scanf("%d%d",&n,&m)!=EOF&&(n||m)){
        scanf("%d",&k);
        count=1;
        memset(map,0,sizeof(map));
        memset(pre,-1,sizeof(pre));
        memset(nmap,0,sizeof(nmap));
        memset(amap,0,sizeof(amap));
        for(int i=1;i<=k;++i){
            scanf("%d%d",&x,&y);
            map[x][y]=1;
        }
        //给图的每个点产生编号
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                if((!map[i][j]))nmap[i][j]=count++;
        //生成邻接矩阵
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                if((!map[i][j]))
                    createmap(i,j);
        //深度搜索
        for(int i=1;i<count;++i){
            memset(visited,0,sizeof(visited));
            dfs(i);
        }
        num=0;
        for(int i=1;i<count;++i){
            if(pre[i]!=-1)num++;
        }
        printf("%d\n",num/2);
    }
    return 0;
}