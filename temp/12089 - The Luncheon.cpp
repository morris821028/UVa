#include <stdio.h> 

int main() {
	int D, N, S, T, x;
	int cases = 0;
	while (scanf("%d", &N) == 1 && N) {
		int A[64] = {}, B[64] = {};
		scanf("%d", &S);
		for (int i = 0; i < S; i++)
			scanf("%d", &x), A[x] = 1;
		scanf("%d", &T);
		for (int i = 0; i < T; i++)
			scanf("%d", &x), B[x] = 1;
		scanf("%d", &D);
		double P[4] = {};
		for (int i = 1; i <= N; i++) {
			if (A[i] == 0 && B[i] == 0)
				P[0]++;
			if (A[i] == 0 && B[i] == 1)
				P[1]++;
			if (A[i] == 1 && B[i] == 0)
				P[2]++;
			if (A[i] == 1 && B[i] == 1)
				P[3]++;
		}
		P[0] /= N, P[1] /= N, P[2] /= N, P[3] /= N;
		double dp[2][128][128] = {};
		int used[2][128][128] = {}, testcase = 0, flag = 0;
		dp[0][0][0] = 1;
		for (int i = 0; i < D; i++) {
			int p = flag, q = !flag;
			flag = !flag; 
			testcase++;
			for (int j = 0; j <= i; j++)
			for (int k = 0; k <= i; k++) {
				if (used[q][j][k] != testcase)
					dp[q][j][k] = 0, used[q][j][k] = testcase;
				if (used[q][j][k+1] != testcase)
					dp[q][j][k+1] = 0, used[q][j][k+1] = testcase;
				if (used[q][j+1][k] != testcase)
					dp[q][j+1][k] = 0, used[q][j+1][k] = testcase;
				if (used[q][j+1][k+1] != testcase)
					dp[q][j+1][k+1] = 0, used[q][j+1][k+1] = testcase;
				dp[q][j][k] += dp[p][j][k] * P[0];
				dp[q][j][k+1] += dp[p][j][k] * P[1];
				dp[q][j+1][k] += dp[p][j][k] * P[2];
				dp[q][j+1][k+1] += dp[p][j][k] * P[3];
			}
		}
		double ret = 0;
		for (int i = 0; i * 2 <= D; i++)
			ret += dp[flag][i][i * 2];
		printf("Case %d: %.5lf\n", ++cases, ret);
	}
	return 0;
}
