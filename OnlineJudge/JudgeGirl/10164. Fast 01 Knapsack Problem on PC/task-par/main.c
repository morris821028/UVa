#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <omp.h>
#include <assert.h>

typedef struct {
	int W, V;
} D;

#define max(x, y) ((x) > (y) ? (x) : (y))
#define min(x, y) ((x) < (y) ? (x) : (y))
static int cmp(const void *p1, const void *p2) {
	int x = ((D *) p1)->W, y = ((D *) p2)->W;
	if (x == y)
		return 0;
	return x < y ? -1 : 1;
}
static void subKnapsack(int n, int m, D E[], int dp[]) {
	memset(dp, 0, sizeof(dp[0]) * (m+1));
	for (int i = 0, sum = 0; i < n; i++) {
		int v = E[i].V, w = E[i].W;
		sum = min(m, sum+w);
		int *P = dp+sum, *Q = dp+sum-w;
		int t = sum - w + 1;
#define UNLOOP { *P = max(*P, *Q+v), P--, Q--; }
#define UNLOOP4 {UNLOOP UNLOOP UNLOOP UNLOOP}
#define UNLOOP8 {UNLOOP4 UNLOOP4}
		for (int j = 0; j+8 <= t; j += 8)
			UNLOOP8;
		for (int j = t/8*8; j < t; j++)
			UNLOOP;
	}
	for (int i = 1; i <= m; i++)
		dp[i] = max(dp[i], dp[i-1]);
}
#define MAXM 5000005
#define MAXN 100005
D E[MAXM];
int dp[2][MAXM];
int main() {
	int N, M;
	omp_set_num_threads(2);
#pragma omp parallel
	{
		cpu_set_t cpuset;
		CPU_ZERO(&cpuset);
		int tid = omp_get_thread_num();
		for (int i = tid*6; i < (tid+1)*6; i++)
			CPU_SET(i, &cpuset);
		assert(sched_setaffinity(0, sizeof(cpuset), &cpuset) == 0);
	}
	while (scanf("%d %d", &N, &M) == 2) {
		for (int i = 0; i < N; i++)
			scanf("%d %d", &E[i].W, &E[i].V);
		qsort(E, N, sizeof(E[0]), cmp);
		static D A[MAXM], B[MAXM];
		int nA = 0, nB = 0;
		{
			long long sumA = 0, sumB = 0;
			for (int i = 0; i < N; i++) {
				if (sumA < sumB)
					A[nA++] = E[i], sumA += E[i].W;
				else
					B[nB++] = E[i], sumB += E[i].W;
			}
		}
#pragma omp parallel sections
		{
#pragma omp section
			{
				subKnapsack(nA, M, A, dp[0]);
			}
#pragma omp section
			{
				subKnapsack(nB, M, B, dp[1]);
			}
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



