#include<stdio.h>
#include<stdlib.h>
main() {
	int T, N, P, R, DP[14][14][14] = {};
	DP[1][1][1] = 1;
	for(N = 2; N <= 13; N++)
		for(P = 1; P <= 13; P++)
			for(R = 1; R <= 13; R++)
				DP[N][P][R] = DP[N-1][P][R]*(N-2) + DP[N-1][P-1][R] + DP[N-1][P][R-1];
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d %d", &N, &P, &R);
		printf("%d\n", DP[N][P][R]);
	}
	return 0;
}

