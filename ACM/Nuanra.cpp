/*
NUANRA Problem
*/
#include<iostream>
#include<set>
using namespace std;

struct colection
{
  int val;
  colection(int i){val=i;}
};
bool operator<(const colection &a,const colection &b){
  if(a.val<b.val)return true;else return false;
}

int main(){
  multiset<colection> base;
  int n,i;char c;
  while(cin>>n&&n!=0){
    while(n--){
      cin>>c;
      if(c=='B'){
        cin>>i;
        base.insert(i);
      }
      else{
        base.erase(base.begin());
      }
      multiset<colection>::iterator setit;
      for(setit=base.begin();setit!=base.end();setit++)
        cout<<(*setit).val<<endl;
    }
  }
  system("pause");
  return 0;
}