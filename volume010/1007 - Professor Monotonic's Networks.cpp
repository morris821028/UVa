#include <bits/stdc++.h>
using namespace std;
// sorting network
const int MAXM = 256;
const int MAXN = 16;
int main() {
	int n, m, cases = 0;
	pair<int, int> cmp[MAXM];
	while (scanf("%d %d", &n, &m) == 2 && n) {
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &cmp[i].first, &cmp[i].second);
			cmp[i].first--, cmp[i].second--;
		}
		
		int ret = 1;
		for (int i = 1; i < (1<<n) && ret; i++) {
			int t = i;
			for (int j = 0; j < m; j++) {
				int a = (t>>cmp[j].first)&1;
				int b = (t>>cmp[j].second)&1;
				if (a == 1 && b == 0) {
					t ^= 1<<cmp[j].first;
					t ^= 1<<cmp[j].second;
				}
			}
			for (int j = (t&(-t)); j < (1<<n); j <<= 1) {
				if ((t&j) == 0) {
					ret = 0;
					break;
				}
			}
		}

		int dp[MAXN] = {}, dep = 0;
		for (int i = 0; i < m; i++) {
			int t = max(dp[cmp[i].first], dp[cmp[i].second])+1;
			dp[cmp[i].first] = t;
			dp[cmp[i].second] = t;
			dep = max(dep, t);
		}
		if (ret == 1) {
			printf("Case %d is a sorting network and operates in %d time units.\n", ++cases, dep);
		} else {
			printf("Case %d is not a sorting network and operates in %d time units.\n", ++cases, dep);
		}
	}
	return 0;
}
/*
4  5
1  2    3  4    1  3
2  4    2  3
8  0
3  3
1  2    2  3    1  2
*/
