#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define oo 100000
int A[100000], HASH[1000000], size;
struct Node {
	int v, st, ed;
	int next;
}Node[100001];
int Ai, Aj;
void Update(int i, int j) {
	if(i < Ai || (Ai == i && j < Aj))
		Ai = i, Aj = j;
}
void insHash(int v, int idx) {
	int m = v%1000000;
	int now = HASH[m], pre = 0;
	while(now) {
		if(Node[now].v > v)
			break;
		else if(Node[now].v == v) {
			Node[now].ed = Node[now].ed < idx ? Node[now].ed : idx;
			Update(Node[now].st, Node[now].ed);
			return;
		}
		else	pre = now, now = Node[now].next;
	}
	size++;
	if(!pre)	HASH[m] = size;
	else		Node[pre].next = size;
	Node[size].v = v, Node[size].st = idx, Node[size].ed = oo;
	Node[size].next = now;
	return;
}
int main(){
	int n, k, i;
	while(scanf("%d", &n) == 1 && n) {
		for(i = 0; i < n; i++)
			scanf("%d", &A[i]);
		scanf("%d", &k);
		memset(HASH, 0, sizeof(HASH) < 4*k ? sizeof(HASH) : 4*k);
		Ai = oo, Aj = oo, size = 0;
		int sum = 0;
		insHash(0, -1);
		for(i = 0; i < n; i++) {
			A[i] %= k;
			sum += A[i];
			sum %= k;
			if(sum < 0) sum += k;
			insHash(sum, i);
		}
		if(Aj != oo)
			printf("%d %d\n", Ai+2, Aj+1);
		else
			puts("no solutions.");
	}
	return 0;
}
