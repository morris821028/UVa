#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;
#define MAXN 512
int A[MAXN];
int dp[MAXN][MAXN] = {}, complete[MAXN][MAXN];
int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		
		for (int i = 1; i < n; i++) { // build cost table.
			for (int j = 0; i + j < n; j++) {
				int l = j, r = i + j;
				int &val = dp[l][r];
				val = 0x3f3f3f3f;
				for (int k = l; k < r; k++) {
					int open = 0; // [l, r] = L[l, k] + R[k+1, r]
					int minL = 0x3f3f3f3f, minR = 0x3f3f3f3f;
					for (int p = l; p <= k; p++)
						minL = min(minL, A[p]);
					for (int p = k+1; p <= r; p++)
						minR = min(minR, A[p]);
					for (int p = l; p <= k; p++)
						open += A[p] > minR;
					for (int p = k+1; p <= r; p++)
						open += A[p] > minL;
//					printf("[%d %d %d %d] %d %d\n", l, k, k+1, r, dp[l][k] + dp[k+1][r]+ open, open);
					val = min(val, dp[l][k] + dp[k + 1][r] + open); 
				}
			}
		}
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; i + j < n; j++) {
				int l = j, r = i + j, m = i + 1; // [l, r] need 1, 2, 3, ..., m
				int used[MAXN] = {}, ok = 1;
				for (int k = l; k <= r && ok; k++) {
					if (A[k] > m) {
						ok = 0;
						break;
					}
					used[A[k]]++;
					if (used[A[k]] > 1)	ok = 0;
				}
				complete[l][r] = ok;
			}
		}
		
		int dp2[MAXN];
		for (int i = 0; i <= n; i++)
			dp2[i] = 0x3f3f3f3f;
		for (int i = 0; i < n; i++) {
			for (int j = i; j < n; j++) {
				if (complete[i][j]) {
					int comb = dp[i][j];
					if (i)	comb += dp2[i-1];
					dp2[j] = min(dp2[j], comb);
				}
			}
		}
		if (dp2[n - 1] == 0x3f3f3f3f)
			puts("impossible");
		else
			printf("%d\n", dp2[n - 1]);
	}
	return 0;
}
/*
7
1 2 1 2 4 3 3
7
1 2 3 2 4 1 3
2
1 1
2 
2 1
5
1 3 2 3 1
5
1 2 2 3 1
*/
