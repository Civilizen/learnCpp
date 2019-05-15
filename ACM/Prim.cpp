/*
Prim解决最小生成树问题
*/
#include <iostream>
#include <queue>
using namespace std;

#define M 20
int G[M][M];
int n;
struct EdgeNode
{
  int start, end;
  int cost;
} edge, result[M];

bool operator<(const EdgeNode &a, const EdgeNode &b)
{
  if (a.cost > b.cost)
    return true;
  else
    return false;
}
priority_queue<EdgeNode> PQ;

//数据输入
void Input()
{
  int i, j;
  cin >> n;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      cin >> G[i][j];
}

void Prim()
{
  int i, j, k;
  int size;
  int startnode = 0;
  int curnode;
  G[startnode][startnode] = 1;
  for (k = 1; k < n; k++)
  {
    edge.start = startnode;
    edge.end = k;
    edge.cost = G[0][k];
    PQ.push(edge);
  }
  for (i = 0; i < n - 1; i++)
  {
    while (!PQ.empty())
    {
      edge = PQ.top();
      PQ.pop();
      curnode = edge.end;
      if (G[curnode][curnode] == 0)
      {
        G[curnode][curnode] = 1;
        result[size] = edge;
        size++;
        for (j = 0; j < n; j++)
          if (G[j][j] == 0 && j != edge.end)
          {
            edge.start = curnode;
            edge.end = j;
            edge.cost = G[curnode][j];
            PQ.push(edge);
          }
        break;
      }
    }
  }
}

void Output()
{
  int i;
  for (i = 0; i < n - 1; i++)
  {
    cout << i << ":  (" << result[i].start << " --->" << result[i].end << " ) : " << result[i].cost << endl;
  }
}
int main()
{
  cout << "please input the data of graph:" << endl;
  Input();
  Prim();
  Output();
  system("pause");
  return 0;
}