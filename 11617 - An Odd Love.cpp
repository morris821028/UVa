#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
char g[1024][1024];
int main() {
	int testcase;
	int n, m;
	int i, j, k;
	int L[1024], R[1024], C[1024];
	int dp[1024][2];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &m, &n);
		int N = 0;
		for(i = 0; i < n; i++) {
			scanf("%s", g[i]);
			int l, r;
			l = r = -1;
			for(j = 0; j < m; j++) {
				if((g[i][j] - '0')%2)
					continue;
				if(l == -1)
					l = j;
				r = j;
			}
			if(l != -1) {
				L[N] = l;
				R[N] = r;
				C[N] = i;
				N++;
			}
		}
		memset(dp, 0x7f, sizeof(dp));
		if(N == 0) {
			puts("0");
			continue;
		}
		int ret = C[N-1];
		for(i = 0; i < N; i++) {
			int pos[2], cost[2];
			if(i == 0)
				pos[0] = pos[1] = cost[0] = cost[1] = 0;
			else {
				pos[0] = L[i-1];
				pos[1] = R[i-1];
				cost[0] = dp[i-1][0];
				cost[1] = dp[i-1][1];
			}
			int c1, c2;
			c1 = abs(pos[0] - R[i]) + R[i] - L[i] + cost[0];
			c2 = abs(pos[1] - R[i]) + R[i] - L[i] + cost[1];
			dp[i][0] = min(c1, c2);
			c1 = abs(pos[0] - L[i]) + R[i] - L[i] + cost[0];
			c2 = abs(pos[1] - L[i]) + R[i] - L[i] + cost[1];
			dp[i][1] = min(c1, c2);
		}
		ret += min(dp[N-1][0], dp[N-1][1]);
		printf("%d\n", ret);
	}
	return 0;
}
