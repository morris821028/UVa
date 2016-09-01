// new line
#include <stdio.h>
#include <omp.h>
#define MAXN 4096
#define INF (1LL<<60)
int N, SZ[MAXN+5];
long long dp[MAXN*MAXN];
int main() {
	while (scanf("%d", &N) == 1) {
        for (int i = 0; i <= N; i++)
            scanf("%d", &SZ[i]);
		for (int i = 0; i < N; i++)
			dp[i*N+i] = 0;	
		if (N > 2048) {
			#pragma offload target(mic)
			#pragma omp parallel firstprivate(N)
			{
				for (int i = 1; i <= N; i++) {
					#pragma omp for
					#pragma ivdep
					for (int j = 0; j < N-i; j++) {
						int l = j, r = j+i;
						long long local = INF, base = 1LL * SZ[l] * SZ[r+1];
						long long *dp1 = dp + l*N, *dp2 = dp + r*N;
						for (int k = l; k < r; k++) {
							long long t = dp1[k] + dp2[k+1] + SZ[k+1] * base;
							if (t < local)
								local = t;
						}
						dp1[r] = dp2[l] = local;
					}
				}
			}
		} else {
			#pragma omp parallel firstprivate(N)
			{
				for (int i = 1; i <= N; i++) {
					#pragma omp for
					#pragma ivdep
					for (int j = 0; j < N-i; j++) {
						int l = j, r = j+i;
						long long local = INF, base = 1LL * SZ[l] * SZ[r+1];
						long long *dp1 = dp + l*N, *dp2 = dp + r*N;
						for (int k = l; k < r; k++) {
							long long t = dp1[k] + dp2[k+1] + SZ[k+1] * base;
							if (t < local)
								local = t;
						}
						dp1[r] = dp2[l] = local;
					}
				}
			}
		}
		printf("%lld\n", dp[0*N+N-1]);
	}
	return 0;
}



