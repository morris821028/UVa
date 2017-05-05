#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h> 
#include <omp.h>
#include <assert.h>
#define MAXM 1000005
#define MAXN 10005

typedef struct {
    int W, V;
} D;
inline static int max(int x, int y) {return x > y ? x : y;}
inline static int min(int x, int y) {return x < y ? x : y;}
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

	while (scanf("%d %d", &N, &M) == 2) {
		for (int i = 0; i < N; i++)
			scanf("%d %d", &E[i].W, &E[i].V);
		memset(dp, 0, sizeof(dp));
		qsort(E, N, sizeof(E[0]), cmp);
#pragma omp parallel
		{
			int sum = 0;
			int tot = omp_get_num_threads();
			int tid = omp_get_thread_num();
			for (int i = 0; i < N; i++) {
				int v = E[i].V, w = E[i].W;
				int *dpQ = dp[(i&1)^1], *dpP = dp[(i&1)];
				sum = min(sum + w, M);
				int l = (sum+1)*tid/tot, r = (sum+1)*(tid+1)/tot;
				if (min(r, w) > l) {
					memcpy(dpQ+l, dpP+l, sizeof(dpQ[0])*(min(r, w)-l));
					l = min(r, w);
				} 
				if (l < r) {
					dpQ += l, dpP += l;
					int *dpPw = dpP-w;
#define UNLOOP {*dpQ = max((*dpPw)+v, *dpP), dpPw++, dpP++, dpQ++;}
#define UNLOOP4 {UNLOOP UNLOOP UNLOOP UNLOOP}
#define UNLOOP8 {UNLOOP4 UNLOOP4}
					int i = l;
					for ( ; i+8 <= r; i += 8)
						UNLOOP8;
					for ( ; i < r; i++)
						UNLOOP;
				}
				#pragma omp barrier
			}
		}
		int ret = 0;
		for (int i = 0; i <= M; i++)
			ret = max(ret, dp[N&1][i]);
		printf("%d\n", ret);
	}
	return 0;
}


