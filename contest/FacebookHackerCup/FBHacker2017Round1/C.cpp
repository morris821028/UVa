#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int N, M, K;
		scanf("%d %d %d", &N, &M, &K);
		
		long long g[105][105] = {};
		const long long INF = 1LL<<60;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++)
				g[i][j] = INF;
			g[i][i] = 0;
		}
		for (int i = 0; i < M; i++) {
			int A, B;
			long long G;
			scanf("%d %d %lld", &A, &B, &G);
			g[A][B] = min(g[A][B], G);
			g[B][A] = min(g[B][A], G);
		}
		
		for (int k = 1; k <= N; k++) {
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= N; j++)
					g[i][j] = min(g[i][j], g[i][k]+g[k][j]);
			}
		}
		
//		for (int i = 1; i <= N; i++) {
//			for (int j = 1; j <= N; j++)
//				printf("%lld ", g[i][j]);
//			puts("");
//		}
		
		int S[5005], D[5005];
		for (int i = 0; i < K; i++)
			scanf("%d %d", &S[i], &D[i]);
		static long long dp[5005][105][2] = {};
		for (int i = 0; i <= K; i++) {
			for (int j = 0; j <= N; j++)
				dp[i][j][0] = INF, dp[i][j][1] = INF;;
		}
		dp[0][1][0] = 0;
		
		for (int i = 0; i < K; i++) {
			int s1 = S[i], d1 = D[i];
			for (int j = 1; j <= N; j++) {
				long long cc;
				cc = g[j][s1]+g[s1][d1];
				dp[i+1][d1][0] = min(dp[i+1][d1][0], dp[i][j][0] + cc);
				cc = g[j][s1];
				dp[i+1][s1][1] = min(dp[i+1][s1][1], dp[i][j][0] + cc);
				
				if (dp[i][j][1] != INF && i > 0) {
					int sP = S[i-1], dP = D[i-1];
					cc = g[j][s1]+g[s1][dP];
					dp[i+1][dP][1] = min(dp[i+1][dP][1], dp[i][j][1] + cc);
					cc = g[j][s1]+g[s1][dP]+g[dP][d1];
					dp[i+1][d1][0] = min(dp[i+1][d1][0], dp[i][j][1] + cc);
				}
			}
			
//			for (int j = 1; j <= N; j++)
//				printf("%lld ", dp[i+1][j][0]);
//			puts("");
		}
		
		long long ret = -1;
		for (int i = 1; i <= N; i++) {
			if (dp[K][i][0] != INF)
				ret = max(ret, dp[K][i][0]);
		}
		printf("Case #%d: %lld\n", ++cases, ret);
	}
	return 0;
}

