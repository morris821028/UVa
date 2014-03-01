#include<stdio.h>
#include<stdlib.h>
#define oo 1000000000
typedef struct {
	int x, y, v;
}Pair;
Pair Path[1000000];
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
int NodeT[1001], NodeL[1001], Q[1000001];
int SPFA(int st, int ed, int N) {
	int i, j, k;
	static int Used[1001], V[1001], QIdx;
	static int DP[1001], tNode;
	for(i = 1; i <= N; i++)
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
	static Pair Tmp[1001];
	for(i = 1; i <= N; i++)
		Tmp[i-1].x = V[i], Tmp[i-1].y = i;;
	DP[st] = 1;
	qsort(Tmp, N, sizeof(Pair), cmp);
	for(i = 0; i < N; i++) {
		tNode = Tmp[i].y;
		for(j = 0, k = NodeL[tNode]; j < NodeT[tNode]; j++, k++) {
			if(V[tNode] < V[Path[k].y] && V[Path[k].y] != oo) {
				DP[Path[k].y] += DP[tNode];
			}
		}
		if(tNode == ed)	break;
	}
	return DP[ed];
}
int main() {
	int N, M, i;
	while(scanf("%d", &N) == 1 && N) {
		scanf("%d", &M);
		for(i = 1; i <= N; i++)
			NodeL[i] = oo, NodeT[i] = 0;
		for(i = 0; i < M; i++) {
			scanf("%d %d %d", &Path[i].x, &Path[i].y, &Path[i].v);
			Path[M+i].x = Path[i].y;
			Path[M+i].y = Path[i].x;
			Path[M+i].v = Path[i].v;
		}
		qsort(Path, 2*M, sizeof(Pair), cmp);
		for(i = 0, M *= 2; i < M; i++) {
			NodeL[Path[i].x] = Min(i, NodeL[Path[i].x]);
			NodeT[Path[i].x] ++;
		}
		printf("%d\n", SPFA(2, 1, N));
	}
	return 0;
}
