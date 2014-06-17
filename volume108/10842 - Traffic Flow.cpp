#include<stdio.h>
#include<stdlib.h>
int Parent[101], Rank[101];
int MakeInit(int n) {
	static int i;
	for(i = 0; i <= n; i++)
		Parent[i] = i, Rank[i] = 1;
}
int FindParent(int x) {
	if(Parent[x] != x)
		Parent[x] = FindParent(Parent[x]);
	return Parent[x];
}
int Link(int x, int y) {
	if(Rank[x] > Rank[y])
		Rank[x] += Rank[y], Parent[y] = x;
	else
		Rank[y] += Rank[x], Parent[x] = y;
}
int Union(int x, int y) {
	x = FindParent(x), y = FindParent(y);
	if(x != y) {
		Link(x, y);
		return 1;
	}
	return 0;
}
typedef struct {
	int x, y, v;
}Path;
Path Data[10000];
int cmp(const void *i, const void *j) {
	Path *a, *b;
	a = (Path *)i, b = (Path *)j;
	return b->v - a->v;
}
int main() {
	int T, Case = 0, n, m, i;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &n, &m);
		MakeInit(n);
		for(i = 0; i < m; i++)
			scanf("%d %d %d", &Data[i].x, &Data[i].y, &Data[i].v);
		qsort(Data, m, sizeof(Path), cmp);
		int edge = 0;
		printf("Case #%d: ", ++Case);
		for(i = 0; i < m; i++) {
			edge += Union(Data[i].x, Data[i].y);
			if(edge == n-1) {
				printf("%d\n", Data[i].v);
				break;
			}
		} 
	}
    return 0;
}
