#include<stdio.h>
#include<string.h>
#include<math.h>
#define oo 10000
int Map[402][402];
int max_flow(int st, int ed, int n) {
	int maxflow = 0, tn, tw, a, b;
	int pre[n+1], V[n+1];
	char Used[n+1];
	int Q[100001], Qt;
	while(1) {
		memset(Used, 0, sizeof(Used));
		memset(V, 0, sizeof(V));
		V[st] = oo;
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
long long GCD(long long x, long long y) {
	int t;
	while(x%y) {
		t = x, x = y, y = t%y;
	}
	return y;
}
main() {
	int n, i, j;
	long long tmp1, tmp2, A[201];
	while(scanf("%d", &n) == 1) {
		memset(Map, 0, sizeof(Map));
		int st = 0, ed = 2*n+1;
		for(i = 1; i <= n; i++)
			scanf("%lld", &A[i]);
		for(i = 1; i <= n; i++)
			for(j = 1; j <= n; j++) {
				tmp1 = A[i]*A[i] + A[j]*A[j];
				tmp2 = (int)sqrt(tmp1);
				if(GCD(A[i], A[j]) == 1 && tmp1 == tmp2*tmp2)
					Map[i][n+j] = 1;
			}
		for(i = 1; i <= n; i++)		Map[st][i] = 1, Map[i+n][ed] = 1;
		printf("%d\n", max_flow(st, ed, 2*n+1)/2);
	}
	return 0;
}
