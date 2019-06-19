#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int parent[100001];

int Find(int i){
    int r = i;
    while(parent[r] >= 0)
        r = parent[r];
    while(r!=i){
        int s = parent[i];
        parent[i] = r;
        i = s;
    }
    return r;
}

void Union(int i,int j){
    int temp = parent[i] + parent[j];
    if(j < i){
        parent[i]=j;
        parent[j]=temp;
    }
    else{
        parent[j]=i;
        parent[i]=temp;
    }

}

int main(){
    int n,m,a,b,j,k;
    int cn=0;
    char c;
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(parent,-1,sizeof(int)*(n+1));
        if(cn)printf("\n");
        cn++;
        printf("Case %d:\n",cn);
        while(m--){
            getchar();
            scanf("%c",&c);
            if(c == 'M'){
                scanf("%d%d",&a,&b);
                a = Find(a);
                b = Find(b);
                if(a != b)Union(a,b);
            }
            else{
                scanf("%d",&j);
                printf("%d\n",-parent[Find(j)]);
            }
        }
    }
    return 0;
}