#include<stdio.h>
#include<stdlib.h>
#define oo 100000
typedef struct {
	int x, y, v;
}Pair;
Pair Path[10001];
int cmp(const void *i, const void *j) {
	Pair *x, *y;
	x = (Pair *)i, y = (Pair *)j;
	if(x->x < y->x)		return -1;
	else if(x->x == y->x)
			return x->v - y->v;
	else	return 1;
}
int Min(int x, int y) {
	return x < y ? x : y; 
}
int NodeT[101], NodeL[101], Q[10001];
int SPFA(int st, int ed, int N) {
	int i, j, k;
	static int Used[101], V[101], QIdx;
	static int DP[101], tNode;
	for(i = 0; i <= N; i++)
		Used[i] = 0, V[i] = oo, DP[i] = 0;
	Used[st] = 1, V[st] = 0, QIdx = 0, Q[QIdx] = st;
	for(i = 0; i <= QIdx; i++) {
		tNode = Q[i], Used[tNode] = 0;
		for(j = 0, k = NodeL[tNode]; j < NodeT[tNode]; j++, k++) {
			if(V[tNode] + Path[k].v < V[Path[k].y]) {
				V[Path[k].y] = V[tNode] + Path[k].v;
				if(!Used[Path[k].y]) {
					Used[Path[k].y] = 1, Q[++QIdx] = Path[k].y;
				}
			}
		}
	}
	return V[ed];
}
int main() {
	int N, M, i;
	while(scanf("%d %d", &N, &M) == 2) {
		for(i = 0; i <= 100; i++)
			NodeL[i] = oo, NodeT[i] = 0;
		for(i = 0; i < M; i++) {
			scanf("%d %d", &Path[i].x, &Path[i].y);
			Path[i].v = 1;
		}
		qsort(Path, M, sizeof(Pair), cmp);
		for(i = 0; i < M; i++) {
			NodeL[Path[i].x] = Min(i, NodeL[Path[i].x]);
			NodeT[Path[i].x] ++;
		}
		puts(SPFA(0, N, 100) != oo ? "Ok!" : "Impossib1e!");
	}
	return 0;
}
