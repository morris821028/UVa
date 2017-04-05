#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (getchar() != '\n');
	while (testcase--) {
		char sa[1024], sb[1024];
		fgets(sa, 128, stdin);
		fgets(sb, 128, stdin);
		
		int dp[128][128] = {};
		int na = strlen(sa)-1, nb = strlen(sb)-1;
		const int INF = 0x3f3f3f3f;
		memset(dp, 0x3f, sizeof(dp));
		dp[0][0] = 0;
		for (int i = 0; i <= na; i++) {
			for (int j = 0; j <= nb; j++) {
				if (sa[i] == sb[j])
					dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j]);
				dp[i+1][j] = min(dp[i+1][j], dp[i][j]+1);
				dp[i][j+1] = min(dp[i][j+1], dp[i][j]+1);
				dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j]+1);
			}
		}
		printf("%d\n", dp[na][nb]);
	}
	return 0;
}
/*
6
impossible
possible

possible
sorry
scared
excused

counted
proud
two people
to
*/
