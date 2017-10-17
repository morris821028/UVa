#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 128;
const int MAXM = 10;
const int MAXS = 100;
int A[MAXN], n;
int main() {
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++) {
			int a, b;
			scanf("%d.%d", &a, &b);
			A[i] = b;
		}
		
		int64_t dp[MAXM][MAXS] = {};
		dp[0][0] = 1;	// [choose #x][sum of {x}] = ways
		
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < MAXS; j++) {
				if (dp[i][j] == 0)
					continue;
				int64_t t = dp[i][j];
				for (int k = 0; k < n; k++)
					dp[i+1][j+A[k]] += t;
			}
		}
		
		int64_t ret = 0;
		for (int i = 0; i < MAXS; i++) {
			if (dp[8][i])
				ret += dp[8][i] * (i/10);
		}
		printf("%lld\n", ret);
	}
	return 0;
}
