#include<iostream>
#include<stdio.h>
#include<queue>
using namespace std;

int knight[8][8];
int x[]={2,1,-1,-2,-2,-1,1,2};
int y[]={1,2,2,1,-1,-2,-2,-1};

struct point
{
    int x,y;
    int moves;
}from,to,tem;

int main(){
    char p1[3],p2[3];
    queue<point> q;
    while (scanf("%s%s",&p1,&p2)!=EOF)
    {
        from.x=p1[0]-'a';
        from.y=p1[1]-'1';
        from.moves=0;
        to.x=p2[0]-'a';
        to.y=p2[1]-'1';
        q.push(from);
        while(!q.empty()){
            from=q.front();q.pop();
            if(from.x==to.x&&from.y==to.y)break;
            for(int i=0;i<8;i++){
                tem.x=from.x+x[i];
                tem.y=from.y+y[i];
                tem.moves=from.moves+1;
                if(tem.x<0||tem.y<0||tem.x>7||tem.y>7)continue;
                q.push(tem);
            }
        }
        while(!q.empty())q.pop();
        printf("To get from %s to %s takes %d knight moves.\n",p1,p2,from.moves);
    }

}