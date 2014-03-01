#include <stdio.h>
int main() {
	int T, M, C, K, i, j, k;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &M, &C);
		int DP[201] = {}, W[201] = {}, A[20];
		for(i = 0; i < C; i++) {
			scanf("%d", &K);
			for(j = 0; j < K; j++)
				scanf("%d", &A[j]);
			for(j = M; j >= 0; j--) {
				int max = 0;
				for(k = 0; k < K; k++) {
					if(j-A[k] >= 0) {
						if(max <= DP[j-A[k]]+A[k] && W[j-A[k]] == i)
							max = DP[j-A[k]]+A[k];
					}
				}
				if(max)	W[j]++;
				DP[j] = DP[j] > max ? DP[j] : max;
				
			}
		}
		int max = 0;
		for(i = 0; i <= M; i++) {
			if(W[i] == C)
				max = max > DP[i] ? max : DP[i];
		} 
		if(max == 0)
			puts("no solution");
		else
			printf("%d\n", max);
	}
    return 0;
}
