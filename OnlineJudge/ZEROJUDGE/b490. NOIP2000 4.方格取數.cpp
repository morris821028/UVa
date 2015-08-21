#include <bits/stdc++.h> 
using namespace std;

int main() {
	int n, x, y, w;
	int A[16][16] = {}, dp[32][16][16] = {};
	scanf("%d", &n);
	while (scanf("%d %d %d", &x, &y, &w) == 3 && x)
		A[x-1][y-1] = w;
	int step = n*2-1;
	for (int i = 1; i <= step; i++) {
		for (int j = 0; j <= n && j <= i; j++) {
			for (int k = 0; k <= n && k <= i; k++) {
				int mxv = 0;
				mxv = dp[i-1][j][k];
				if (j)
					mxv = max(mxv, dp[i-1][j-1][k]);
				if (k)
					mxv = max(mxv, dp[i-1][j][k-1]);
				if (j && k)
					mxv = max(mxv, dp[i-1][j-1][k-1]);
				dp[i][j][k] = mxv + (j != k ? A[i-j][j] + A[i-k][k] : A[i-j][j]);
			}
		}
	}
	int ret = 0;
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			ret = max(ret, dp[step][i][j]);
	printf("%d\n", ret + A[0][0]);
	return 0;
}
/*
8
2 3 13
2 6 6
3 5 7
4 4 14
5 2 21 
5 6 4
6 3 15
7 2 14
0 0 0
8
1 2 1
2 1 1
0 0 0
*/
