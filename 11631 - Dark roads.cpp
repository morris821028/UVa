#include <stdio.h>
#include <stdlib.h>
#define maxN 400000 
typedef struct {
	int x, y, v;
}Link;
Link D[maxN];
int Parent[maxN], Rank[maxN];
void MakeInit(int n) {
	int i;
	for(i = 0; i <= n; i++)
		Parent[i] = i, Rank[i] = 1;
}
int FindParent(int x) {
	if(Parent[x] != x)
		Parent[x] = FindParent(Parent[x]);
	return Parent[x];
}
void PLink(int x, int y) {
	if(Rank[x] > Rank[y]) {
		Rank[x] += Rank[y];
		Parent[y] = x;
	} else {
		Rank[y] += Rank[x];
		Parent[x] = y;
	}
}
int Union(int x, int y) {
	x = FindParent(x), y = FindParent(y);
	if(x != y) {
		PLink(x, y);
		return 1;
	}
	return 0;
}
int cmp(const void *i, const void *j) {
	Link *a, *b;
	a = (Link *)i, b = (Link *)j;
	return a->v - b->v;
}
int main() {
	int N, M;
	while(scanf("%d %d", &N, &M) == 2) {
		if(N == 0 && M == 0)
			break;
		int sum = 0, i, test = 0, flag;
		for(i = 0; i < M; i++) {
			scanf("%d %d %d", &D[i].x, &D[i].y, &D[i].v);
			D[M+i].x = D[i].y;
			D[M+i].y = D[i].x;
			D[M+i].v = D[i].v;
			sum += D[i].v;
		}
		M = M*2;
		qsort(D, M, sizeof(Link), cmp);
		MakeInit(N);
		for(i = 0; i < M; i++) {
			flag = Union(D[i].x, D[i].y);
			sum -= flag * D[i].v;
			test += flag;
			if(test == N-1)		break;
		}
		printf("%d\n", sum);
	}
    return 0;
}
