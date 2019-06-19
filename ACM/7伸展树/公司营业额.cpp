#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<time.h>
using namespace std;
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define INF 1<<30
long i, sum = 0;
struct node {
	node* child[2], * par;
	int val, weight;
	node() {
		child[0] = child[1] = par = 0;
		val = weight = 0;
	}
}*root;

void turn(node* x, int d) {
	//d=0左旋,d=1右旋
	node* y = x->par;
	y->child[!d] = x->child[d];
	if (x->child[d])x->child[d]->par = y;
	x->par = y->par;
	if (y->par) {
		if (y == y->par->child[0])
			y->par->child[0] = x;
		else
			y->par->child[1] = x;
	}
	x->child[d] = y;
	y->par = x;
}

void Splay(node* x, node* y) {
	while (x->par != y) {
		if (x->par->par == y) {
			x->par->child[0] == x ? turn(x, 1) : turn(x, 0);
		}
		else if (x->par->par->child[0] == x->par) {
			if (x->par->child[0] == x) { turn(x->par, 1); turn(x, 1); }
			else { turn(x, 0); turn(x, 1); }
		}
		else {
			if (x->par->child[1] == x) { turn(x->par, 0); turn(x, 0); }
			else { turn(x, 1); turn(x, 0); }
		}
	}
	if (y == 0)root = x;
}

bool Find(node* x, long key) {
	if (!x)return false;
	if (x->val == key) {
		Splay(x, 0);
		return true;
	}
	else {
		if (x->val < key)
			return Find(x->child[1], key);
		else
			return Find(x->child[0], key);
	}
}

void Insert(int key) {
	node* p, * TT, * father; TT = root; father = 0;
	while (TT != 0) {
		if (key == TT->val) { TT->weight++; Splay(TT, 0); return; }
		else if (key < TT->val) {
			father = TT; TT = TT->child[0];
		}
		else { father = TT; TT = TT->child[1]; }
	}
	p = new node; p->val = key; p->weight = 1;
	p->child[0] = p->child[1] = 0; p->par = father;
	if (father == 0)root = p;
	else if (key > father->val)father->child[1] = p;
	else father->child[0] = p;
	Splay(p, 0);
}

int main() {
	srand((unsigned)time(NULL));
	root = 0;
	node* q;
	long a, b;
	for (i = 1; i <= 32767; ++i) {
		a = -1; b = INF;
		Insert((rand()*RAND_MAX)%1000000);
		if (i == 1) { sum += root->val; continue; }//第一个
		if (root->weight > 1)continue;//有重复
		else {//无重复
			if (q = root->child[0]) {
				while (q->child[1])q = q->child[1];
				a = q->val;
			}
			if (q = root->child[1]) {
				while (q->child[0])q = q->child[0];
				b = q->val;
			}
			sum += min(root->val - a, b - root->val);
		}
	}
	printf("%d ", sum);
    system("pause");
	return 0;
}