#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 8005
using namespace std;
struct Node{
    int ld,rd;
    int color;
}Tree[4*maxn];
int cnt[maxn],temp;
void buildtree(int i,int a,int b){
    Tree[i].ld=a;
    Tree[i].rd=b;
    Tree[i].color=-1;
    if(a==b-1)return;
    buildtree(i*2,a,(a+b)/2);
    buildtree(i*2+1,(a+b)/2,b);
}
void Insert(int i,int a,int b,int color){
    if(a<=Tree[i].ld&&Tree[i].rd<=b){
        Tree[i].color=color;
        return;
    }
    if(Tree[i].color!=-1){
        Tree[i*2].color=Tree[i*2+1].color=Tree[i].color;
        Tree[i].color=-1;
    }
    if(a>=(Tree[i].ld+Tree[i].rd)/2)
        Insert(i*2+1,a,b,color);
    else if(b<=(Tree[i].ld+Tree[i].rd)/2)
        Insert(i*2,a,b,color);
    else{
        Insert(i*2,a,(Tree[i].ld+Tree[i].rd)/2,color);
        Insert(i*2+1,(Tree[i].ld+Tree[i].rd)/2,b,color);
    }
}
void count(int i){
    if(Tree[i].color!=-1){
        if(Tree[i].color!=temp)
            cnt[Tree[i].color]++;
        temp=Tree[i].color;
        return;
    }
    if(Tree[i].ld==Tree[i].rd-1){
        temp=-1;
        return;
    }
    count(i*2);
    count(i*2+1);

}
int main(){
    int n,x1,x2,c;
    while(scanf("%d",&n)!=EOF){
        buildtree(1,0,maxn);
        for(int i=0;i<n;++i){
            scanf("%d%d%d",&x1,&x2,&c);
            Insert(1,x1,x2,c);
        }
        temp=-1;
        memset(cnt,0,sizeof(cnt));
        count(1);
        for (int i=0; i<maxn; i++)
            if(cnt[i])
                printf ("%d %d\n", i, cnt[i]);
        printf("\n");
    }
    return 0;
}