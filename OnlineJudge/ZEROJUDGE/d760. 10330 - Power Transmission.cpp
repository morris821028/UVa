#include<stdio.h>
#define MaxV 10000000
#define MinV 0
int Map[205][205];
int max_flow(int st, int ed, int n) {
	int maxflow = 0, tn , tw;
	int pre[205], V[205], a, b;
	int Q[50000], Qt;
	while(1) {
		int Used[205] = {};
		for(a = 0; a <= n; a++)
			V[a] = MinV;
		V[st] = MaxV;
		Qt = 0, Q[0] = st, pre[st] = st;
		for(a = 0; a <= Qt; a++) {
			tn = Q[a], Used[tn] = 0;
			for(b = 0; b < n; b++) {
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
	while(scanf("%d", &n) == 1) {
		st = 0, ed = 2*n + 1;
		for(a = 0; a <= ed; a++)
			for(b = 0; b <= ed; b++)
				Map[a][b] = 0;
		for(a = 1; a <= n; a++) {
			scanf("%d", &v);
			Map[a][a+n] = v;
		}
		scanf("%d", &m);
		for(a = 0; a < m; a++) {
			scanf("%d %d %d", &x, &y, &v);
			if(x == y) continue;
			Map[x+n][y] += v;
		}
		scanf("%d %d", &x, &y);
		for(a = 0; a < x; a++) {
			scanf("%d", &v);
			Map[st][v] = MaxV;
		}
		for(a = 0; a < y; a++) {
			scanf("%d", &v);
			Map[v+n][ed] = MaxV;
		}
		printf("%d\n", max_flow(st, ed, ed+1));
	}
	return 0;
}
