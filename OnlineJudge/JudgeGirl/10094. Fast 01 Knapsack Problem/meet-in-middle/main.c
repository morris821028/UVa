#include <stdio.h>
#include <stdlib.h>

static inline int max(int a, int b) {
	return a > b ? a : b;
}
void subKnapsack(int n, int m, int w[], int v[], int dp[]) {
	memset(dp, 0, sizeof(dp[0]) * (m+1));
	for (int i = 0; i < n; i++) {
		int vv = v[i], ww = w[i];
		for (int j = m; j >= ww; j--)
			dp[j] = max(dp[j], dp[j-ww]+vv);
	}
}
#define MAXM 1000005
#define MAXN 100005
int W[MAXN], V[MAXN];
int dp[2][MAXM];
int main() {
	int N, M;
	while (scanf("%d %d", &N, &M) == 2) {
		for (int i = 0; i < N; i++)
			scanf("%d %d", &W[i], &V[i]);
		memset(dp, 0, sizeof(dp));
		
		#pragma omp parallel sections
		{
			#pragma omp section
			subKnapsack(N/2, M, W, V, dp[0]);
			#pragma omp section
			subKnapsack(N-N/2, M, W+N/2, V+N/2, dp[1]);
		}
				
		int ret = 0;
		for (int i = M, j = 0, mx = 0; i >= 0; i--) {
			mx = max(mx, dp[1][j]), j++;
			ret = max(ret, dp[0][i] + mx);
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
4 5
2 3
1 2 
3 4
2 2
*/



