#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct {
	int x, y;
	double v;
}Link;
struct {
	double x, y;
}P[100];
Link D[10001];
int cmp(const void *i, const void *j) {
	Link *a, *b;
	a = (Link *)i, b = (Link *)j;
	return a->v - b->v < 0 ? -1 : 1;
}
int Parent[100], Rank[100];
void MakeInit(int n) {
	int i;
	for(i = 0; i < n; i++)
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
int main() {
	int T, n;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		int m = 0, i, j;
		for(i = 0; i < n; i++)
			scanf("%lf %lf", &P[i].x, &P[i].y);
		for(i = 0; i < n; i++) {
			for(j = 0; j < n; j++) {
				if(i != j) {
					D[m].x = i, D[m].y = j;
					D[m].v = sqrt((P[i].x-P[j].x)*(P[i].x-P[j].x)+
						(P[i].y-P[j].y)*(P[i].y-P[j].y));
					m++;
				}
			}
		}
		qsort(D, m, sizeof(Link), cmp);
		double sum = 0;
		MakeInit(n);
		for(i = 0; i < m; i++) {
			sum += Union(D[i].x, D[i].y)*D[i].v;
		}
		printf("%.2lf\n", sum);
		if(T)	puts("");
	}
    return 0;
}
