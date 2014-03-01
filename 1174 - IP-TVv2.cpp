#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct {
	int x, y, v;
}Path;
Path D[50001];
int cmp(const void *i, const void *j) {
	Path *a, *b;
	a = (Path *)i, b = (Path *)j;
	return a->v - b->v;
}
struct {
	int son[128];
	int code;
}Trie[60001];
int TrieSize;
int Recode(int *n, char *name) {
	static int i, j;
	for(i = 0, j = 0; name[i]; i++) {
		if(!Trie[j].son[name[i]])
			Trie[j].son[name[i]] = ++TrieSize;
		j = Trie[j].son[name[i]];
	}
	if(!Trie[j].code)
		Trie[j].code = (*n)++;
	return Trie[j].code;
}
int Parent[2001], Rank[2001];
int MakeSet(int N) {
	static int i;
	for(i = 1; i <= N; i++)
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
	char B[31], E[31];
	scanf("%d", &T);
	while(T--) {
		size = 1, TrieSize = 0;
		scanf("%d %d", &M, &N);
		memset(Trie, 0, sizeof(Trie));
		for(i = 0; i < N; i++) {
			scanf("%s %s %d", B, E, &C);
			x = Recode(&size, B);
			y = Recode(&size, E);
			D[i].x = x, D[i].y = y, D[i].v = C;
		}
		qsort(D, N, sizeof(Path), cmp);
		MakeSet(M);
		int Ans = 0;
		for(i = 0; i < N; i++)
			Ans += D[i].v * Union(D[i].x, D[i].y);
		printf("%d\n", Ans);
		if(T)	puts("");
	}
    return 0;
}
