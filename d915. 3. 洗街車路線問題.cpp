#include<stdio.h>
#include<stdlib.h>
#define oo 1000000000
typedef struct {
    int x, y, v;
}Pair;
Pair Path[2250001];
int cmp(const void *i, const void *j) {
    Pair *x, *y;
    x = (Pair *)i, y = (Pair *)j;
    if(x->x < y->x)        return -1;
    else if(x->x == y->x)
            return x->v - y->v;
    else    return 1;
}
int Min(int x, int y) {
    return x < y ? x : y;
}
int NodeT[1501], NodeL[1501], Q[2250001];
int Map[16][16];
void SPFA(int st, int N, int Idx) {
    int i, j, k;
    static int Used[1501], V[1501], QIdx;
    static int DP[1501], tNode;
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
    for(i = 1, j = 0; i <= N; i++)
    	if(NodeT[i]%2)
    		Map[Idx][j] = V[i], j++;
}
int Best[65537], Idx;
int DP(int N, int sum) {
    if(N == 0)    return 0;
    if(Best[N] != oo)
        return Best[N];
    if(Best[sum] == oo)
        Best[sum] = DP(sum, 0);
    int i, j, tmp;
    for(i = 0; i < Idx; i++) {
        if(N&(1<<i)) {
            for(j = i+1; j < Idx; j++) {
                if(N&(1<<j)) {
                    tmp = DP(N-(1<<i)-(1<<j), sum+(1<<i)+(1<<j));
                    Best[N] = Best[N] < tmp+Map[i][j] ? Best[N] : tmp+Map[i][j];
                }
            }
            break;
        }
    }
    return Best[N];
}
int main() {
    int N, M, S, i, j;
    while(scanf("%d %d %d", &N, &M, &S) == 3) {
		int Sum = 0;
        for(i = 1; i <= N; i++)
            NodeL[i] = oo, NodeT[i] = 0;
        for(i = 0; i < M; i++) {
            scanf("%d %d %d", &Path[i].x, &Path[i].y, &Path[i].v);
            Path[M+i].x = Path[i].y;
            Path[M+i].y = Path[i].x;
            Path[M+i].v = Path[i].v;
            Sum += Path[i].v;
        }
        qsort(Path, 2*M, sizeof(Pair), cmp);
        for(i = 0, M *= 2; i < M; i++) {
            NodeL[Path[i].x] = Min(i, NodeL[Path[i].x]);
            NodeT[Path[i].x] ++;
        }
        Idx = 0;
        for(i = 1; i <= N; i++) {
			if(NodeT[i]%2)
				SPFA(i, N, Idx), Idx++;
		}
		for(i = (1<<Idx)-1; i >= 0; i--)
			Best[i] = oo;
		Best[0] = 0;
		printf("%d\n", DP((1<<Idx)-1, 0)+Sum);
    }
    return 0;
}
