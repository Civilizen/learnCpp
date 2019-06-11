#include<stdio.h>
int main(void){
  char str[255];int tot,i;
  while(1){
    gets(str);
    if(str[0]=='#')break;
    tot=0;i=1;
    while(str[i-1]!='\0'){
      if(str[i-1]==' '){i++;continue;}
      tot=tot+(str[i-1]-64)*i;i++;
    }
    printf("%d\n",tot);
  }
  return 0;
}