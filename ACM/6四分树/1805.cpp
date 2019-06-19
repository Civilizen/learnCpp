#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
int M[129][129];//输入的数据图

class quadtree{
public:
    int cnt;//压缩后的结点数
    int sum;//未压缩之前的结点数
    int value;//0--全0 1--全1 2--混合
    quadtree *child[4];
    quadtree():cnt(1),sum(1){
        child[0]=child[1]=child[2]=child[3]=NULL;
    }
    bool operator!=(const quadtree&p)const{
        //判断两个子树是否是不同的
        if(value==2||value!=p.value)
            return true;
        else
            return false;
    }
    bool operator==(const quadtree&p){
        //判断两树是否相似
        if(this==&p)
            return true;
        if(value!=p.value)
            return false;
        for(int i=0;i<4;++i){
            if(!(*child[i]==*p.child[i])){
                return false;
            }
        }
        return true;
    }
};

vector<quadtree*>tab;
quadtree *head;

quadtree *check_dup(quadtree *p){//判断有没有存在的相似子树
    for(int i=0;i<tab.size();i++){
        if(*tab[i] == *p){
            delete p;
            return tab[i];
        }
    }
    tab.push_back(p);
    return p;
}

quadtree* DFS(int r,int c,int len){
    int i;
    bool f=true;
    quadtree *temp = new quadtree;
    if(len==1){
        temp->value=M[r][c];
        return temp;
    }
    len/=2;
    temp->child[0]=DFS(r,c,len);
    temp->child[1]=DFS(r,c+len,len);
    temp->child[2]=DFS(r+len,c,len);
    temp->child[3]=DFS(r+len,c+len,len);
    for(i=1;i<4;i++){
        if(*temp->child[0]!=*temp->child[i]){
            f=false;
            break;
        }
    }
    if(f){
        temp->value=temp->child[0]->value;
        for(i=0;i<4;++i){
            delete temp->child[i];
            temp->child[i]=NULL;
        }
    }
    else{
        temp->value=2;
        for(int i=0;i<4;++i){
            temp->sum+=temp->child[i]->sum;
            temp->cnt+=temp->child[i]->cnt;
            temp->child[i]->cnt=0;
        }
        temp=check_dup(temp);
    }
    return temp;
}
void FreeAll(){
    for(int j=0;j<tab.size();j++){
        delete tab[j];
    }
    tab.clear();
}

int main(){
    int row,col,n;
    char ch;
    while(scanf("%d%d",&row,&col)&&(row+col)){
        n=1;
        while(n<row||n<col){
            n*=2;
        }
        //getchar();
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i<row&&j<col){
                    scanf(" %c",&ch);
                    M[i][j]=ch-'0';
                }
                else{
                    M[i][j]=0;
                }
            }
            //getchar();
        }


        head=DFS(0,0,n);
        printf("%d %d\n", head->sum, head->cnt);
        FreeAll();
    }
    //system("pause");
    return 0;
}