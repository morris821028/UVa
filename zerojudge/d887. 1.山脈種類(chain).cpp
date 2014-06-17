#include<stdio.h>
main() {
	int n, a, b;
	while(scanf("%d", &n) == 1) {
		long long DP[27][27] = {0};
		DP[0][1] = 1;
		for(a = 1; a <= n + 1; a++)
			for(b = a; b <= n + 1; b++)
				DP[a][b] = DP[a-1][b] + DP[a][b-1];
		printf("%llu\n", DP[n+1][n+1]);
	}
	return 0;
}
