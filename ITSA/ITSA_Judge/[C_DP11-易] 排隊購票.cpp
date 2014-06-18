#include <stdio.h> 

int main() {
	int a, b;
	while(scanf("%d,%d", &a, &b) == 2) {
		int dp[55][55] = {};
		dp[0][0] = 1;
		for(int i = 0; i <= a; i++) {
			for(int j = 0; j <= b; j++) {
				if(i == 0 && j == 0)
					continue;
				if(i)
					dp[i][j] += dp[i-1][j];
				if(j > 0 && i >= j)
					dp[i][j] += dp[i][j-1];
			}
		}
		printf("%d\n", dp[a][b]);
	}
	return 0;
}
