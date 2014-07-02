#include <stdio.h> 
#include <string.h>

long long dp[1<<16];
int used[1<<16], mark[16];
int n, testcase;
long long dfs(int state, int mm) {
	if(used[state] == testcase)
		return dp[state];
	if(state == (1<<n) - 1)
		return 1;
	used[state] = testcase;
	long long &ret = dp[state];
	ret = 0;
	for(int i = 0; i < n; i++) {
		if(((state>>i)&1) == 0 && ((mm>>i)&1) != 0) {
			ret += dfs(state|(1<<i), mm|mark[i]);
		}
	}
	return ret;
}
int main() {
	char s[128];
	int cases = 0;
	scanf("%*d");
	while(scanf("%d", &n) == 1) {
		scanf("%s", s);
		int start = 0;
		for(int i = 0; i < n; i++)
			start |= ((s[i] == '1')<<i);
		for(int i = 0; i < n; i++) {
			scanf("%s", s);
			mark[i] = 0;
			for(int j = 0; j < n; j++)
				mark[i] |= ((s[j] == '1')<<j);
		}
		testcase++;
		printf("Case %d: %lld\n", ++cases, dfs(0, start));
	}
	return 0;
}
/*
3
1
1
1
2
11
01
10
3
110
011
100
000
*/
