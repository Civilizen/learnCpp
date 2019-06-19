#include<iostream>
#include<cstdio>
#include<map>
#include<string>
using namespace std;

int main(){
    string a,b;
    map<string,string>M;
    while (scanf("%s",&a)&&a!="\n"){
        scanf("%s",&b);
        M[b]=a;
    }
    while(scanf("%d",&b)&&b!="\n"){
        printf("%s\n",M[b]);
    }
    return 0;
}