#include <iostream>
#include <cstdio>
#include <cstdlib>
#define oo 100000000
using namespace std;
typedef struct {
	int x, y, l, k;
}Path;
Path Map[1001];
int cmp(const void *i, const void *j) {
	Path *x, *y;
	x = (Path *)i, y = (Path *)j;
	return x->x - y->x;
}
int min(int x, int y) {
	return x < y ? x : y;
}
int NodeL[51], NodeT[51];
int Queue[10000000];
void SPFA(int st, int ed, int n, int kind) {
	int i, j, k, l, Qt;
	int V[51][51], Cut = oo;
	for(i = 1; i <= n; i++)
		for(j = 0; j <= kind; j++)
			V[i][j] = oo;
	V[st][0] = 0, Queue[0] = st, Qt = 0;
	for(i = 0; i <= Qt; i++) {
		int tn = Queue[i];
		for(j = 0, k = NodeL[tn]; j < NodeT[tn]; j++, k++) {
			for(l = 0; l <= kind; l++)
				if(l != Map[k].k) {
					if(V[Map[k].y][Map[k].k] > V[tn][l] + Map[k].l) {
						V[Map[k].y][Map[k].k] = V[tn][l] + Map[k].l;
						if(V[Map[k].y][Map[k].k] <= Cut)
							Queue[++Qt] = Map[k].y;
						if(Map[k].y == ed)
							Cut = min(Cut, V[Map[k].y][Map[k].k]);
					}
				}
		}
	}
	int Min = oo;
	for(i = 0; i <= kind; i++)
		Min = min(Min, V[ed][i]);
	if(Min == oo)
		printf("infinity\n");
	else
		printf("%d\n", Min);
}
int main() {
	int T, i, n, m, k, p;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d %d %d", &n, &m, &k, &p);
		for(i = 1; i <= n; i++)
			NodeL[i] = oo, NodeT[i] = 0;
		for(i = 0; i < m; i++) {
			scanf("%d %d %d %d", &Map[i].x, &Map[i].y, &Map[i].l, &Map[i].k);
			Map[i+m].x = Map[i].y;
			Map[i+m].y = Map[i].x;
			Map[i+m].l = Map[i].l;
			Map[i+m].k = Map[i].k;
		}
		m *= 2;
		qsort(Map, m, sizeof(Path), cmp);
		int st, ed;
		for(i = 0; i < m; i++) {
			NodeL[Map[i].x] = min(NodeL[Map[i].x], i);
			NodeT[Map[i].x]++;
		}
		while(p--) {
			scanf("%d %d", &st, &ed);
			SPFA(st, ed, n, k);
		}
	}
	return 0;
}
