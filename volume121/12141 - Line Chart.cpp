#include <stdio.h> 
#include <vector>
#include <string.h>
#include <algorithm>
#include <map>
using namespace std;

int dp[10005][64][3] = {};
const int mod = 1000000;
int main() {
	freopen("in.txt", "r+t", stdin);
	freopen("out.txt", "w+t", stdout);
	int testcase, n, m, x, y;
	int cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		vector< pair<int, int> > D;
		map<int, int> R;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			R[y] = 0;
			D.push_back(make_pair(x, y));
		}
		sort(D.begin(), D.end());
		int v = 0;
		for (map<int, int>::iterator it = R.begin();
			it != R.end(); it++)
			it->second = v++;
		for (int i = 0; i < n; i++)
			D[i].second = R[D[i].second];
		memset(dp, 0, sizeof(dp));
		int used[10005] = {};
		for (int i = 0; i < n; i++) {
			if (used[D[i].second] == 0) {
				dp[i][0][0] = 1; // =
				dp[i][0][1] = 1; // <
				dp[i][0][2] = 1; // > next time
				used[D[i].second] = 1;
			}
		}
		int ret = 0;
		if (m == 0)
			ret++;
		for (int i = 0; i < n; i++) {
			ret = (ret + dp[i][m][0])%mod;
			memset(used, 0, sizeof(used));
//			for (int k = 0; k <= m; k++) 
//					printf("[%d %d] %d %d %d\n", i, k, dp[i][k][0], dp[i][k][1], dp[i][k][2]);
			for (int j = i+1; j < n; j++) {					
				if (used[D[j].second])	continue;
				used[D[j].second] = 1;
				for (int k = 0; k <= m; k++) {
					if (D[j].second > D[i].second) { // larger
						dp[j][k][0] = (dp[j][k][0] + dp[i][k][2])%mod;
						dp[j][k+1][1] = (dp[j][k+1][1] + dp[i][k][2])%mod;
						dp[j][k][2] = (dp[j][k][2] + dp[i][k][2])%mod;
					} else if (D[j].second == D[i].second) {
//						dp[j][k][0] = (dp[j][k][0] + dp[i][k][0])%mod;
//						dp[j][k][1] = (dp[j][k][1] + dp[i][k][0])%mod;
//						dp[j][k][2] = (dp[j][k][2] + dp[i][k][0])%mod;
					} else {
						dp[j][k][0] = (dp[j][k][0] + dp[i][k][1])%mod;
						dp[j][k][1] = (dp[j][k][1] + dp[i][k][1])%mod;
						dp[j][k+1][2] = (dp[j][k+1][2] + dp[i][k][1])%mod;
					}
				}
			}
		}
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}
/*
3
6 1
320 3
306 1
401 3
325 4
393 5
380 2
4 1
101 3
102 2
103 2
104 4
3 0
102 2
101 1
103 3
*/
