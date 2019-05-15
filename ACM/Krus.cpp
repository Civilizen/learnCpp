/*
Krus解决最小生成树问题算法
*/
#include <iostream>
#include<string.h>
#include <queue>
using namespace std;

#define M 20
#define N 50
#define Maxsize 100  //并查集的存储空间量
int parent[Maxsize];  //并查集数组

int n;
int G[M][M];

struct EdgeNode
{                 //最小生成树的树边结点
  int start, end; //两顶点位置
  int cost;       //权值
} edge, result[M];

bool operator<(const EdgeNode &a, const EdgeNode &b)
{
  if (a.cost > b.cost)
    return true;
  else
    return false;
}

priority_queue<EdgeNode> PQ;

//并查集
struct linknode
{
  int data;
  struct linknode *next;
} * adj[M];

//数据输入
void Input()
{
  int i, j;
  cin >> n;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      cin >> G[i][j];
}

//将边加入优先队列中
void Change()
{
  int i, j;
  for (i = 0; i < n; i++)
    for (j = i + 1; j < n; j++)
      if (G[i][j] != 32767)
      {
        edge.cost = G[i][j];
        edge.start = i;
        edge.end = j;
        PQ.push(edge); //  进入优先队列
      }
}

int SetFind(int i) //找到含元素i的树的树根
{
  int r;
  for(r=i;parent[r]>=0;r=parent[r]); //找到根
  while(i!=r)   //坍塌树
  {
    int s = parent[i];
    parent[i]=r;
    i=s;
  }
  return r;
}

void SetUnion(int i,int j)  //基于权重规则构造以i和j为根的集合的并
{
  int temp=parent[i]+parent[j];
  if(parent[j]<parent[i])
  {parent[i]=j;parent[j]=temp;}//树i的结点少
  else
  {parent[j]=i;parent[i]=temp;}//树j的结点少或与树i的结点同样多

}

void KrusSet()
{
  int pos1, pos2;
  int choose;
  memset(parent,-1,sizeof(parent));
  choose=0;
  while(choose<n-1)
  {
    edge=PQ.top();PQ.pop();
    pos1=SetFind(edge.start);
    pos2=SetFind(edge.end);
    if(pos1!=pos2)
    {
      SetUnion(pos1,pos2);
      result[choose].start=pos1;
      result[choose].end=pos2;
      result[choose].cost=edge.cost;
      choose++;
    }
  }
}

//生成并查集的n个树根，置成初始状态
void createadj()
{
  int i;
  struct linknode *p;
  for (i = 0; i < n; i++)
  {
    p = new linknode; // 生成链表
    p->data = i;
    p->next = NULL;
    adj[i] = p;
  }
}

//Krus生成最小生成树
void Krus()
{
  int k;
  int pos1, pos2;
  int choose;
  struct linknode *p;
  createadj(); //并查集生成
  choose = 0;
  while (choose < n - 1)
  {
    edge = PQ.top();
    PQ.pop(); //出列
    for (k = 0; k < n; ++k)
    {
      p = adj[k];
      while (p)
      {
        if (p->data == edge.start)
          pos1 = k;
        if (p->data == edge.end)
          pos2 = k;
        p = p->next;
      }
    }
    if (pos1 != pos2)
    { //没有回路
      p = adj[pos1];
      while (p->next != NULL)
        p = p->next;
      p->next = adj[pos2];
      adj[pos2]=NULL; //串连在一起
      result[choose].start=pos1;
      result[choose].end=pos2;
      result[choose].cost=edge.cost;
      choose++;
    }
  }
}

void Output()
{
  int i;
  for(i=0;i<n-1;i++)
  {
    cout<<i<<":  ("<<result[i].start<<" --->"<<result[i].end<<" ) : "<<result[i].cost<<endl;
  }
}

int main(){
  Input();
  Change();
  //Krus();
  KrusSet();
  Output();
  system("pause");
  return 0;
}