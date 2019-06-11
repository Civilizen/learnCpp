#include<stdio.h>
int main(){
  int i,j,k;
  scanf("%d",&i);
  while(i>0){
    scanf("%d",&j);
    for(k=0;j!=0;k++){
      if(j%2==1){
        if(j/2==0)printf("%d\n",k);
        else printf("%d ",k);
      }
      j/=2;
    }
    i--;
  }
  return 0;
}