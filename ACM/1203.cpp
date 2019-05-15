/*
ZOJ1203
Prim算法解决
Input:
5
0 0
0 1
1 1
1 0
0.5 0.5
*/
#include <iostream>
#include <math.h>
#include <stdio.h>
#include<string.h>
using namespace std;
double dis[105][105];
double p[105][2];
double ans;
int n;

void Makedis()
{
  int i, j;
  double r;
  for (i = 1; i <= n; ++i)
    for (j = 1; j <= n; j++)
    {
      r = sqrt((p[i][0] - p[j][0]) * (p[i][0] - p[j][0]) + (p[i][1] - p[j][1]) * (p[i][1] - p[j][1]));
      dis[i][j] = r;
    }
}

void Prim()
{
  int i, j, k;
  int temp[105];
  double min;
  int ia, ib;
  memset(temp, 0, sizeof(temp));
  temp[1] = 1;
  for (k = 1; k <= n - 1; k++)
  {
    min = 1.0e8;
    for (i = 1; i <= n; i++)
      if (temp[i] == 1)
      {
        for (j = 1; j <= n; j++)
          if (temp[j] == 0 && dis[i][j] < min)
          {
            min = dis[i][j];
            ia = i;
            ib = j;
          }
      }
    ans += min;
    temp[ib] = 1;
  }
}
int main()
{
  int t,step=0;int i,j,k;
  while(scanf("%d",&n))
  {
    step++;
    ans=0;
    if(n==0)break;
    if(step!=1)printf("\n");
    for(i=1;i<=n;i++)
    {
      scanf("%lf%lf",&p[i][0],&p[i][1]);
    }
    Makedis();
    Prim();
    printf("Case #%d:\n",step);
    printf("The minimal distance is: %.2lf\n",ans);
  }
  return 0;
}