#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;
#define MAXN 128
char A[MAXN], B[MAXN];
int f[MAXN][MAXN]; // cost from 'x...xx' to B[l, r]
int dp[MAXN];
int solve() {
	int n = strlen(A+1);
	memset(f, 63, sizeof(f));
	for (int i = 1; i <= n; i++) {
		f[i][i] = 1;
		if (i+1 <= n)
			f[i][i+1] = B[i] == B[i+1] ? 1 : 2;
	}
	for (int i = 2; i <= n; i++) {
		for (int j = 1; j+i <= n; j++) {
			int l = j, r = j+i;
			for (int k = l; k < r; k++)
				f[l][r] = min(f[l][r], f[l][k] + f[k+1][r]);
			if (B[l] == B[r]) {
				f[l][r] = min(f[l][r], f[l+1][r]);
				f[l][r] = min(f[l][r], f[l][r-1]);
			}
		}
	}
	
	memset(dp, 63, sizeof(dp));
	dp[0] = 0;
	for (int i = 0; i <= n; i++) {		
		if (i && A[i] == B[i])
			dp[i] = min(dp[i], dp[i-1]);
		for (int j = i+1; j <= n; j++)
			dp[j] = min(dp[j], dp[i] + f[i+1][j]);
	}
	return dp[n];
}
int main() {
	while (scanf("%s %s", A+1, B+1) == 2) {
		int ret = solve();
		printf("%d\n", ret);
	}
	return 0;
} 
