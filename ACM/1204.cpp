/*
Problem:ZOJ1204
*/
#include<iostream>
#include<stdio.h>
#include<set>
using namespace std;

int main(){
  int n,m,i;
  set<int> base;
  scanf("%d",&n);
  while(n--){
    scanf("%d",&m);
    while(m--){
      scanf("%d",&i);
      base.insert(i);
    }


    base.clear();
  }
  system("pause");
  return 0;
}