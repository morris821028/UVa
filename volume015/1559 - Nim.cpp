#include <bits/stdc++.h>
using namespace std;

const int MAXS = 2<<13;
int n, s, m[32];

int dp[32][MAXS];
int dfs(int idx, int s) {
	if (s <= 0)
		return 1;
	if (idx >= n)	idx -= n;
	int &ret = dp[idx][s];
	if (ret != -1)
		return ret;
	ret = 0;
	for (int i = 1; i <= m[idx] && !ret; i++)
		ret |= !dfs(idx+1, s-i);
	return ret;
}
int main() {
	while (scanf("%d", &n) == 1 && n) {
		scanf("%d", &s);
		n <<= 1;
		for (int i = 0; i < n; i++)
			scanf("%d", &m[i]);
		
		memset(dp, -1, sizeof(dp));
		int ret = dfs(0, s);
		printf("%d\n", ret);
	}
	return 0;
}
/*
1 101 4 4
1 100 4 4
3 97 8 7 6 5 4 3
0
*/
