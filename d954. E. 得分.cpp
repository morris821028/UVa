#include<stdio.h>
main() {
	int T, N, S, a, b;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &N, &S);
		long long A[100], DP[10001] = {};
		for(a = 0; a < N; a++)
			scanf("%lld", &A[a]);
		DP[0] = 1;
		for(a = 0; a < N; a++)
			for(b = A[a]; b <= S; b++)
				DP[b] += DP[b-A[a]];
		printf("%lld\n", DP[S]);
	}
	return 0;
}
