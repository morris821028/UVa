#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define mod 100000
int HASH[mod], size;
struct Node {
	int v, next;
}Node[1049000];
int insHASH(int v) {
	static int m;
	m = v%mod;
	int pre = 0, now = HASH[m];
	while(now) {
		if(Node[now].v < v)
			pre = now, now = Node[now].next;
		else if(Node[now].v == v)
			return 0;
		else
			break;
	}
	size++;
	if(!pre)	HASH[m] = size;
	else		Node[pre].next = size;
	Node[size].v = v;
	Node[size].next = now;
	return 1;
}
int freeHASH() {
	memset(HASH, 0, sizeof(HASH));
}
int cmp(const void *i, const void *j) {
	return *(int *)j - *(int *)i;
}
int DP[1049000];
int main() {
	int n, A[20], i, j, Dt, tmp;
	while(scanf("%d", &n) == 1) {
		freeHASH();
		int sum = 0, max = 0, before;
		for(i = 0; i < n; i++)
			scanf("%d", &A[i]), sum += A[i];
		qsort(A, n, sizeof(int), cmp);
		Dt = 0, DP[0] = 0, tmp = sum/2, size = 0;
		for(i = 0; i < n; i++) {
			for(j = 0, before = Dt; j <= before; j++) {
				if(A[i]+DP[j] <= tmp) {
					if(insHASH(A[i]+DP[j]))		DP[++Dt] = A[i]+DP[j];
					max = max > A[i]+DP[j] ? max : A[i]+DP[j];
				}
			}
		}
		printf("%d\n", sum-2*max);
	}
	return 0;
}
