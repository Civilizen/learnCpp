#include <iostream>
#include<cstdio>
#define  maxn 50000
#define  MAX  99999
using namespace std;
#define min(a, b) (((a) < (b)) ? (a) : (b))
struct node
{
	int l;
	int r;
	int key = MAX;
};

node tree[500000];

void buildTree(int index, int a, int b)
{
	//赋值
	tree[index].l = a;
	tree[index].r = b;
	tree[index].key=MAX;
	if (b == a)
		return;
	int middle = (a + b) / 2;
	buildTree(index * 2 , a, middle);
	buildTree(index * 2 + 1, middle+1, b);
}

int findMinKey(int i, int a, int b){
	if (a == tree[i].l&&b == tree[i].r){
		return tree[i].key;
	}
	int mid=(tree[i].l+tree[i].r)/2;
	if(b<=mid) return findMinKey(2*i,a,b);
	if(a>mid) return findMinKey(2*i+1,a,b);
	int min1,min2;
	min1 = findMinKey(2 * i, a, mid);
	min2 = findMinKey(2 * i + 1, mid+1, b);
	return min(min1,min2);
}

void resetMinkey(int i,int p,int x){
	if(x<tree[i].key)tree[i].key=x;
	if(tree[i].l==tree[i].r)return;
	if(p<=(tree[i].l+tree[i].r)/2) resetMinkey(2*i,p,x);
	else resetMinkey(2*i+1,p,x);
}

int main(){
	int n, m,p;
	while (scanf("%d %d", &n, &m) != EOF){
		buildTree(1, 1, n);
		resetMinkey(1,1,0);
		int a, b;
		for (int i = 0; i < m; i++){
            scanf("%d%d", &a, &b);
			if(a<b){
            	p=findMinKey(1,a,b-1);
				resetMinkey(1,b,p+1);
			}
		}
		printf("%d\n",findMinKey(1,n,n));
	}
}