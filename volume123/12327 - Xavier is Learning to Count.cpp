#include <bits/stdc++.h>
using namespace std;

const int MAXN = 13005;
int main() {
	int testcase, cases = 0;
	int n, m;
	static int A[MAXN];
	static int64_t dp[6][5*MAXN];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		sort(A, A+n);
		int mx[6];
		for (int i = 0; i <= m; i++)
			mx[i] = 0;		
		dp[0][0] = 1;
		for (int i = 0; i < n; i++) {
			int w = A[i];
			for (int j = m; j > 0; j--) {
				for (int k = 0; k <= mx[j-1]; k++)
					dp[j][k+w] += dp[j-1][k];
				mx[j] = mx[j-1]+w;
			}
		}

		printf("Case #%d:\n", ++cases);
		for (int i = 0; i <= mx[m]; i++) {
			if (dp[m][i])
				printf("%d: %lld\n", i, dp[m][i]);
		}
		puts("");

		for (int i = 0; i <= m; i++)
			memset(dp[i], 0, sizeof(dp[0][0])*(mx[i]+1));
	}
	return 0;
}
/*
3
3  3
1  2  3
5  4
1  3  5  6  7
10  3
1  2  3  4  5  6  7  8  9  10
*/
