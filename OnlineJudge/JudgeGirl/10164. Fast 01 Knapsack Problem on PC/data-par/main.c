#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <omp.h>
#include <assert.h>
#define MAXM 5000005
#define MAXN 10005
 
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
		for (int i = 0; i < 6; i++)
			CPU_SET(i, &cpuset);
		assert(sched_setaffinity(0, sizeof(cpuset), &cpuset) == 0);
	} 
	while (scanf("%d %d", &N, &M) == 2) {
		for (int i = 0; i < N; i++)
			scanf("%d %d", &E[i].W, &E[i].V);
		memset(dp, 0, sizeof(dp));
		qsort(E, N, sizeof(E[0]), cmp);
		int chunk = M/24;
		if (chunk < 1024)
			chunk = 1024;
#pragma omp parallel
		{
			int sum = 0;
			for (int i = 0; i < N; i++) {
				int p = i&1, q = (i&1)^1;
				{
					int pp = p, qq = q;
					int v = E[i].V, w = E[i].W;
					int *dpQ = dp[qq], *dpP = dp[pp];
					sum = min(sum + w, M);
#pragma omp for schedule(static, chunk)
					for (int i = 0; i <= sum; i++) {
						if (i >= w)
							dpQ[i] = max(dpP[i-w]+v, dpP[i]);
						else
							dpQ[i] = dpP[i];
					}
				}
			}
		}
		int ret = 0;
		for (int i = 0; i <= M; i++)
			ret = max(ret, dp[N&1][i]);
		printf("%d\n", ret);
	}
	return 0;
}


