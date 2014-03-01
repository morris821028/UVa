#include<stdio.h>
#include<stdlib.h>
#define MaxV 2147483647
#define MinV 0
int Map[101][101];
int max_flow(int st, int ed, int n) {
	int maxflow = 0, tn , tw;
	int pre[101], V[101], a, b;
	int Q[30001], Qt;
	while(1) {
		int Used[101] = {};
		for(a = 0; a <= n; a++)
			V[a] = MinV;
		V[st] = MaxV;
		Qt = 0, Q[0] = st, pre[st] = st;
		for(a = 0; a <= Qt; a++) {
			tn = Q[a];
			for(b = 0; b < n; b++) {
				tw = (V[tn] < Map[tn][b]) ? V[tn] : Map[tn][b];
				if(tw > V[b]) {
					V[b] = tw, pre[b] = tn;
					if(Used[b] == 0)
						Q[++Qt] = b, Used[b] = 1;
				}
			}
			Used[tn] = 0;
		}
		if(V[ed] == 0) break;
		maxflow += V[ed];
		printf("%d\n", V[ed]);
		for(a = ed; a != st; a = pre[a]) {
			Map[pre[a]][a] -= V[ed], Map[a][pre[a]] += V[ed];
			printf("(%d %d) %d\n", pre[a], a, Map[pre[a]][a]);
			printf("(%d %d) %d\n", a, pre[a], Map[a][pre[a]]);
			system("pause");
		}
	}
	return maxflow;
}
/*
4 4
3 5
2 2
1 2 3
1 3 3
2 4 1
3 4 3
*/
main() {
	int m, w, a, b, v, st, ed, x, y;
	int C = 0;
	while(scanf("%d %d", &m, &w) == 2) {
		st = 1, ed = m;
		if(m == 0 && w == 0) break;
		for(a = 1; a <= 2*m; a++)
			for(b = 1; b <= 2*m; b++)
				Map[a][b] = 0;
		for(a = 3; a <= m; a++) {
			scanf("%d %d", &x, &v);
			Map[x][x+m] = v;
		}
		Map[1][1+m] = MaxV;
		for(a = 0; a < w; a++) {
			scanf("%d %d %d", &x, &y, &v);
			if(x == y) continue;
			Map[x+m][y] += v;
			Map[y+m][x] += v;
		}
		printf("%d\n", max_flow(st, ed, 2*m));
	}
	return 0;
}
