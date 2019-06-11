#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
int n,m;
vector<int> v,path;
vector<vector<int>>equation;

void display(const vector<int>& equ){
  int tot=equ[0];
  printf("%d",equ[0]);
  for(int i=1;i<equ.size();i++){
    tot+=equ[i];
    printf("+%d",equ[i]);
  }
  printf("=%d\n",tot);
}

bool cmp(const vector<int>& a,const vector<int>& b){
  if(a.size()<b.size())return true;
  if(a.size()>b.size())return false;
  return a<b;
}

void DFS(const int& pos,const int& sum){
  if(pos==m||sum>v.back())return;
  if(binary_search(v.begin()+pos,v.end(),sum))
    equation.push_back(path);
  path.push_back(v[pos]);
  DFS(pos+1,sum+v[pos]);
  path.pop_back();
  DFS(pos+1,sum);
}

int main(){
  scanf("%d",&n);
  while(n--){
    scanf("%d",&m);
    v.resize(m);
    for(int i=0;i<m;i++)
      scanf("%d",&v[i]);
    sort(v.begin(),v.end());
    DFS(0,0);
    sort(equation.begin(),equation.end(),cmp);
    if(equation.empty())
      printf("Can't find any equations.\n");
    else
    {
      for(int i=0;i<equation.size();i++){
        if(i==0||equation[i]!=equation[i-1])
        display(equation[i]);
      }
    }
    printf("\n");
    path.clear();
    equation.clear();
  }
  //system("pause");
  return 0;
}