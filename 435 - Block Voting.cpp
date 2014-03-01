#include <stdio.h>

int main() {
	int t, P, A[20], i, j, k;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &P);
		int sum = 0;
		for(i = 0; i < P; i++)
			scanf("%d", &A[i]), sum += A[i];
		int half = sum/2 + (sum&1);
		for(i = 0; i < P; i++) {
			int DP[1001] = {};
			DP[0] = 1;
			for(j = 0; j < P; j++) {
				if(i == j)	continue;
				for(k = sum-A[j]; k >= 0; k--)
					DP[k+A[j]] += DP[k];
			}
			int ans = 0;
			for(j = half-A[i]; j < half && j >= 0; j++) {
					ans += DP[j];
			}
			printf("party %d has power index %d\n", i+1, ans);
		}
		puts("");
	}
    return 0;
}
