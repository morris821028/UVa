#include <stdio.h>
#include <stdlib.h>
#define maxN 1000001
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
	int N, K, M, a, b, c, flag = 0;
	while(scanf("%d", &N) == 1) {
		int sum = 0, i, j;
		for(i = 1; i < N; i++) {
			scanf("%d %d %d", &a, &b, &c);
			sum += c;
		}
		if(flag)	puts("");
		flag = 1;
		printf("%d\n", sum);
		scanf("%d", &K);
		for(i = 0; i < K; i++)
			scanf("%d %d %d", &D[i].x, &D[i].y, &D[i].v);
		scanf("%d", &M);
		for(i = 0, j = K; i < M; i++, j++)
			scanf("%d %d %d", &D[j].x, &D[j].y, &D[j].v);
		M = K+M, sum = 0;
		qsort(D, M, sizeof(Link), cmp);
		MakeInit(N);
		for(i = 0; i < M; i++)
			sum += Union(D[i].x, D[i].y) * D[i].v;
		printf("%d\n", sum);
	}
    return 0;
}
