#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int N, M;
		scanf("%d %d", &N, &M);
		int dp[305][305] = {};
		const int INF = 0x3f3f3f3f;
		for (int i = 0; i <= N; i++) {
			for (int j = 0; j <= N; j++)
				dp[i][j] = INF;
		}
		
		dp[0][0] = 0;
		for (int i = 0; i < N; i++) {
			int A[305];
			for (int j = 0; j < M; j++)
				scanf("%d", &A[j]);
			sort(A, A+M);
			for (int j = 0, sum = 0; j < M; j++) {
				sum += A[j];
				A[j] = sum;
			}
			for (int j = i; j < N; j++) {
				if (dp[i][j] == INF)
					continue;
				for (int k = 0; k < M && k+j <= N; k++) {
					dp[i+1][j+k+1] = min(dp[i+1][j+k+1], dp[i][j] + A[k] + (k+1)*(k+1));
				}
			}
			for (int j = i+1; j <= N; j++)
				dp[i+1][j] = min(dp[i+1][j], dp[i][j]);
		}
		printf("Case #%d: %d\n", ++cases, dp[N][N]);
	}
	return 0;
}

