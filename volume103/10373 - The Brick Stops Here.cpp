#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
int dp[20005][25];
int main() {
	int n, c, m, cmx, cmn;
	int testcase = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		int w, p;
		memset(dp, 0x3f, sizeof(dp));
		dp[0][0] = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &w, &p);
			for (int j = 20000; j >= w; j--)
				for (int k = 1; k <= 20; k++)
					dp[j][k] = min(dp[j][k], dp[j-w][k-1] + p);
		}
		
		scanf("%d", &c);
		while (c--) {
			scanf("%d %d %d", &m, &cmn, &cmx);
			if (m > n) {
				puts("impossible");
				continue;
			}
			int ret = INF;
			cmn *= m, cmx *= m;
			for (int i = cmn; i <= cmx; i++)
				ret = min(ret, dp[i][m]);
			if (ret != INF)
				printf("%d\n", ret);
			else
				puts("impossible");
		}
		if (testcase)
			puts("");
	}
	return 0;
}
/*
1
11
550 300
550 200
700 340
300 140
600 780
930 785
730 280
678 420
999 900
485 390
888 800
3
2 500 620
9 550 590
9 610 620
*/
