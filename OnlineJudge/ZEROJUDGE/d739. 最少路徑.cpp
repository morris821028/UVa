#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MaxV 10000000
#define MinV 0 
char Map[2002][2002];
int Q[100001], Qt;
char Used[2002] = {};
int max_flow(int st, int ed, int n) {
	int maxflow = 0, tn , tw;
	int pre[2002], V[2002], a, b;
	while(1) {
		memset(Used, 0, sizeof(Used));
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
struct {
	int in, out;
}Boat[1001];
main() {
	int n, x, y, a, b;
	while(scanf("%d", &n) == 1) {
		memset(Map, 0, sizeof(Map));
		int st = 0, ed = 2*n+1;
		for(a = 1; a <= n; a++)
			scanf("%d %d", &Boat[a].in, &Boat[a].out);
		for(a = 1; a <= n; a++)
			for(b = 1; b <= n; b++) {
				if(Boat[a].in > Boat[b].in && Boat[a].out < Boat[b].out)
					Map[a][n+b] = 1;
				if(Boat[a].in > Boat[b].out)
					Map[a][n+b] = 1;
			}
		for(a = 1; a <= n; a++)
			Map[st][a] = 1, Map[a+n][ed] = 1;
		printf("%d\n", n-max_flow(st, ed, 2*n+1));
	}
	return 0;
}
