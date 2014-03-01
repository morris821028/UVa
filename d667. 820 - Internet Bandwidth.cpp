#include<stdio.h>
#define MaxV 10000000
#define MinV 0
int Map[101][101];
int max_flow(int st, int ed, int n) {
	int maxflow = 0, tn , tw;
	int pre[101], V[101], a, b;
	int Q[10001], Qt;
	while(1) {
		int Used[101] = {};
		for(a = 0; a <= n; a++)	V[a] = MinV;
		V[st] = MaxV;
		Qt = 0, Q[0] = st, pre[st] = st;
		for(a = 0; a <= Qt; a++) {
			tn = Q[a], Used[tn] = 0;
			for(b = 1; b <= n; b++) {
				tw = (V[tn] < Map[tn][b]) ? V[tn] : Map[tn][b];
				if(tw > V[b]) {
					V[b] = tw, pre[b] = tn;
					if(Used[b] == 0)
						Q[++Qt] = b, Used[b] = 1;
				}
			}
		}
		if(V[ed] == 0) break;
		maxflow += V[ed];
		for(a = ed; a != st; a = pre[a]) {
			Map[pre[a]][a] -= V[ed], Map[a][pre[a]] += V[ed];
		}
	}
	return maxflow;
}
main() {
	int n, m, a, b, v, st, ed, x, y;
	int C = 0;
	while(scanf("%d", &n) == 1 && n) {
		scanf("%d %d %d", &st, &ed, &m);
		for(a = 1; a <= n; a++)
			for(b = 1; b <= n; b++)
				Map[a][b] = 0;
		for(a = 0; a < m; a++) {
			scanf("%d %d %d", &x, &y, &v);
			Map[x][y] += v;
			Map[y][x] += v;
		}
		printf("Network %d\n", ++C);
		printf("The bandwidth is %d.\n\n", max_flow(st, ed, n));
	}
	return 0;
}
