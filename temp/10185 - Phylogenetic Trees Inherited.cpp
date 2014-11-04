#include <stdio.h>

char acid[1024][1024], ret[2048];
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2 && n) {
		for (int i = 0; i < n; i++)
			scanf("%s", acid[i]);
		ret[m] = '\0';
		int diff = 0, N = 2 * n;
		for (int i = 0; i < m; i++) {
			int dp[2048] = {};
			for (int j = n; j < N; j++)
				dp[j] = 1<<(acid[j - n][i] - 'A');
			for (int j = n-1; j > 0; j--) {
				dp[j] = dp[j<<1]&dp[j<<1|1];
				if (dp[j] == 0) { // choose one branch, cost 1
					diff++;
					dp[j] = dp[j<<1]|dp[j<<1|1];
				}
			}
			for (int j = 0; j < 26; j++) {
				if ((dp[1]>>j)&1) {
					ret[i] = j + 'A';
					break;
				}
			}
		}
		printf("%s %d\n", ret, diff);
	}
	return 0;
}
