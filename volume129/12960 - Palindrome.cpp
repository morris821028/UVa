#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2048;
pair<int, int> dp[MAXN][MAXN];

int main() {
	char s[MAXN];
	int sp[MAXN];
	while (scanf("%s", s) == 1) {
		int n = (int) strlen(s), m, x;
		memset(sp, 0, sizeof(sp));
		scanf("%d", &m);
		for (int i = 0; i < m; i++)
			scanf("%d", &x), sp[x-1] = 1;
		
		pair<int, int> ret(0, 0);
		for (int k = 0; k < n; k++) {
			for (int i = 0; i+k < n; i++) {
				int l = i, r = i+k;
				if (l == r) {
					dp[l][r] = make_pair(sp[l], 1);
				} else {
					dp[l][r] = max(dp[l+1][r], dp[l][r-1]);
					if (s[l] == s[r]) {
						pair<int, int> tmp(dp[l+1][r-1].first+sp[l]+sp[r], dp[l+1][r-1].second+2);
						dp[l][r] = max(dp[l][r], tmp);
					}
				}
				ret = max(ret, dp[l][r]);
			}
		}
		printf("%d\n", ret.second);
	}
	return 0;
}
/*
BANANAS
0
BANANAS
1 7
ACDAAACX
3 2 3 8
MARATONA
4 3 1 5 2
*/
