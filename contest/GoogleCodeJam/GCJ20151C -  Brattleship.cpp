#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;

int dp[1<<20], R, C, W;
int isEnd(int u) {
	int place = (1<<W)-1;
	int v = 0;
	for (int i = 0; i < C - W; i++) {
		if (((u>>i)&place) == 0) 
			return 0; 
		v = min(v, __builtin_popcount(((u>>i)&place)));
	}
	return W - v;
}
int dfs(int u) {
	if (isEnd(u))
		return isEnd(u);
	if (dp[u] != -1)
		return dp[u];
	int &ret = dp[u];
	ret = 0x3f3f3f3f;
	for (int i = 0; i < C; i++) {
		if ((u>>i)&1)
			continue;
		ret = min(ret, dfs(u|(1<<i)) + 1);
	}
	return ret;
}
int solve() {
	memset(dp, -1, sizeof(dp));
	int v = dfs(0);
	return v + (R-1) * (C/W);
}
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d", &R, &C, &W);
		printf("Case #%d: %d\n", ++cases, solve());
	}
	return 0;
}
/*
999
1 5 1
1 10 3
 
3
1 4 2
1 7 7
2 5 1
*/
