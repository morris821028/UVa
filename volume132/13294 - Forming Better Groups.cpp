#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, d, g[21];
	static int64_t dp[1<<21];
	while (scanf("%d %d", &n, &d) == 2 && n) {
		for (int i = 0; i < n; i++)	
			scanf("%d", &g[i]);
		sort(g, g+n);
		memset(dp, 0, sizeof(dp[0])*(1<<n));
		dp[0] = 1;
		for (int i = 0; i < (1<<n); i++) {
			if (dp[i] == 0)
				continue;
			int mn = -1;
			for (int j = 0; j < n; j++) {
				if (((i>>j)&1) == 0)
					mn = j, j = n;
			}
			if (mn >= 0) {
				for (int j = mn+2; j < n; j++) {
					if ((i>>j)&1)
						continue;
					if (g[j] - g[mn] > d)
						break;
					for (int k = mn+1; k < j; k++) {
						if ((i>>k)&1)
							continue;
						dp[i|(1<<mn)|(1<<j)|(1<<k)] += dp[i];
					}
				}
			}
		}
		printf("%lld\n", dp[(1<<n)-1]);
	}
	return 0;
}
/*
6 3
1 6 3 2 4 5
6 8
1 3 3 3 6 5
9 2
1 2 3 4 5 6 7 8 10
0 0
*/
