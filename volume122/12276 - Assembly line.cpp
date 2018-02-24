#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, q, cases = 0;
	const int MAXS = 205;
	char s[MAXS], dict[MAXS];
	while (scanf("%d", &n) == 1 && n) {
		if (cases++)	puts("");
		int R[26] = {}, c[26][26][2];
		for (int i = 0; i < n; i++) {
			scanf("%s", s);
			R[s[0]-'a'] = i, dict[i] = s[0];
		}
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int x;
				scanf("%d-%s", &x, s);
				c[i][j][0] = x, c[i][j][1] = R[s[0]-'a'];
			}
		}
		
		scanf("%d", &q);
		static int dp[MAXS][MAXS][26];
		for (int it = 0; it < q; it++) {
			scanf("%s", s);
			int m = strlen(s);
			for (int i = 0; i < m; i++)
				s[i] = R[s[i]-'a'];
			const int INF = 0x3f3f3f3f;
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < m; j++)
					fill(dp[i][j], dp[i][j]+n, INF);
				dp[i][i][s[i]] = 0;
			}
			for (int i = 1; i < m; i++) {
				for (int j = 0; i+j < m; j++) {
					int l = j, r = i+j;
					for (int k = l; k < r; k++) {
						for (int p = 0; p < n; p++) {
							int lc = dp[l][k][p];
							if (lc == INF)
								continue;
							for (int q = 0; q < n; q++) {
								int rc = dp[k+1][r][q];
								if (rc == INF)
									continue;
								int a = c[p][q][1], b = c[p][q][0];
								dp[l][r][a] = min(dp[l][r][a], lc+rc+b);
							}
						}
					}
				}
			}

			int ret = INF, ret_sym = 0;
			for (int i = 0; i < n; i++) {
				if (dp[0][m-1][i] < ret)
					ret = dp[0][m-1][i], ret_sym = i;
			}
			printf("%d-%c\n", ret, dict[ret_sym]);
		}
	}
	return 0;
}
/*
2
a b
3-b 5-b
6-a 2-b
2
aba
bba
2
m e
5-e 4-m
3-e 4-m
1
eme
0
*/
