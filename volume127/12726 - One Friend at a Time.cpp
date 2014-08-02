#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int dp[1<<20], mask[20], N, M, K;
int used[1<<20] = {}, ucases = 0;
int dfs(int mm) {
	if((mm>>(N-1))&1) 		return 0;
	if(used[mm] == ucases)	return dp[mm];
	int &ret = dp[mm];
	ret = 0x3f3f3f3f, used[mm] = ucases;
	for(int i = 0; i < N; i++) {
		if((mm>>i)&1)	continue;
		int common = __builtin_popcount(mm&mask[i]);
		if(common >= K)
			ret = min(ret, dfs(mm|(1<<i)) + 1);
	}
	return ret;
}
int main() {
	int testcase, cases = 0, x, y;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d %d", &N, &M, &K);
		for(int i = 0; i < N; i++)
			mask[i] = 1<<i;
		for(int i = 0; i < M; i++) {
			scanf("%d %d", &x, &y), x--, y--;
			mask[x] |= 1<<y;
			mask[y] |= 1<<x;
		}
		if((mask[0]>>(N-1))&1) {
			printf("Case #%d: %d\n", ++cases, 0);
			continue;
		}
		ucases ++;
		int ret = dfs(mask[0]);
		printf("Case #%d: %d\n", ++cases, ret == 0x3f3f3f3f ? -1 : (ret - 1));
	}
	return 0;
}
/*
3
3 2 1
1 2
2 3
7 6 1
1 2
2 3
3 4
4 5
5 6
6 7
4 3 2
1 2
2 4
3 4
*/
