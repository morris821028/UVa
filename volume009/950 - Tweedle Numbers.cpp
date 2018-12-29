#include <bits/stdc++.h> 
using namespace std;


int dp[40][40][40][2]; // [digits][runs][consecutive][head digit]

int main() {
	int M, N, K, Q;
	char s[40];
	int cases = 0;
	while (scanf("%d %d %d", &N, &K, &M) == 3) {
		if (cases++)
			puts("");
		memset(dp, 0, sizeof(dp));
		dp[1][1][1][0] = 1;
		dp[1][1][1][1] = 1;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= K; j++) {
				for (int k = 1; k <= M; k++) {
					dp[i+1][j][k+1][0] += dp[i][j][k][0];
					dp[i+1][j][k+1][1] += dp[i][j][k][1];
					dp[i+1][j+1][1][1] += dp[i][j][k][0];
					dp[i+1][j+1][1][0] += dp[i][j][k][1];
				}
			}
		}
		
//		int tot = 0;
//		for (int i = 0; i <= M; i++)
//			tot += dp[N][K][i][1];
//		printf("Total %d\n", tot);
		scanf("%d", &Q);
		while (Q--) {
			scanf("%s", s);
			int run = 0, con = 0;
			int id = 1;
			for (int i = 0; i < N; i++) {
				if (s[i] == '1' && i) {
					int inc = 0;
					if (s[i-1] == '0') {
						for (int k = 0; k <= M-con; k++)
							inc += dp[N-i][K-run+1][k][0];
					} else {
						for (int k = 0; k <= M; k++)
							inc += dp[N-i][K-run][k][0];
					}
//					printf("inc %d, %d %d\n", inc, con, run);
					id += inc;
				}
				if (i > 0 && s[i] == s[i-1]) {
					con++;
				} else {
					run++, con = 1;
				}				
			}
			printf("%d\n", id);
		}
	}
	return 0;
}
/*
6 3 3
4
111011
100011
110011
100111

*/
