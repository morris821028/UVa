#include <stdio.h>
#include <stdlib.h>
int P[30], R[30];
int MakeInit(int N) {
	int i;
	for(i = 0; i <= N; i++)
		P[i] = i, R[i] = 1;
}
int FindP(int x) {
	if(P[x] != x)
		P[x] = FindP(P[x]);
	return P[x];
} 
int Link(int x, int y) {
	if(R[x] > R[y])
		P[y] = x, R[x] += R[y];
	else
		P[x] = y, R[y] += R[x];
}
int Union(int x, int y) {
	x = FindP(x), y = FindP(y);
	if(x != y) {
		Link(x, y);
		return 1;
	}
	return 0;
}
typedef struct {
	int x, y, v;
}Path;
int cmp(const void *i, const void *j) {
	Path *a, *b;
	a = (Path *)i, b = (Path *)j;
	if(a->v != b->v)
		return a->v - b->v;
	if(a->x != b->x)
		return a->x - b->x;
	return a->y - b->y;
}
int main() {
	int T, N, C = 0, i, j, tmp;
	char cha;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &N);
		Path D[1000];
		int M = 0;
		for(i = 0; i < N; i++) {
			for(j = 0; j < N; j++) {
				scanf("%d%c", &tmp, &cha);
				if(i < j && tmp)
					D[M].x = i, D[M].y = j, D[M].v = tmp, M++;
			}
		}
		MakeInit(N);
		qsort(D, M, sizeof(Path), cmp);
		printf("Case %d:\n", ++C);
		for(i = 0; i < M; i++) {
			if(Union(D[i].x, D[i].y) == 1)
				printf("%c-%c %d\n", D[i].x+'A', D[i].y+'A', D[i].v);
		}
	}
    return 0;
}
