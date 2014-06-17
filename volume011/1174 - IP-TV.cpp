#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct {
	int x, y, v;
}Path;
Path D[50000];
int cmp(const void *i, const void *j) {
	Path *a, *b;
	a = (Path *)i, b = (Path *)j;
	return a->v - b->v;
}
int Recode(int *n, char *name, char Buf[][31]) {
	static int i;
	for(i = 0; i < *n; i++)
		if(!strcmp(name, Buf[i]))
			return i;
	strcpy(Buf[i], name);
	(*n)++;
	return i;
}
int Parent[2000], Rank[2000];
int MakeSet(int N) {
	static int i;
	for(i = 0; i < N; i++)
		Parent[i] = i, Rank[i] = 1;
}
int FindP(int x) {
	if(x != Parent[x])
		Parent[x] = FindP(Parent[x]);
	return Parent[x];
}
int Link(int x, int y) {
	if(Rank[x] < Rank[y])
		Parent[x] = y, Rank[x] += Rank[y];
	else
		Parent[y] = x, Rank[y] += Rank[x];
}
int Union(int x, int y) {
	x = FindP(x), y = FindP(y);
	if(x != y) {
		Link(x, y);
		return 1;
	}
	return 0;
}
int main() {
	int T, M, N, C, size, i, x, y;
	char B[31], E[31], Buf[2000][31];
	scanf("%d", &T);
	while(T--) {
		size = 0;
		scanf("%d %d", &M, &N);
		for(i = 0; i < N; i++) {
			scanf("%s %s %d", B, E, &C);
			x = Recode(&size, B, Buf);
			y = Recode(&size, E, Buf);
			D[i].x = x, D[i].y = y, D[i].v = C;
		}
		qsort(D, N, sizeof(Path), cmp);
		MakeSet(N);
		int Ans = 0;
		for(i = 0; i < N; i++)
			Ans += D[i].v * Union(D[i].x, D[i].y);
		printf("%d\n", Ans);
		if(T)	puts("");
	}
    return 0;
}
