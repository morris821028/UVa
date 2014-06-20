#include <stdio.h> 
#include <algorithm>
#include <iostream>
using namespace std;
#define MAXN 45
int N, pile[4][MAXN];
int used[MAXN][MAXN][MAXN][MAXN] = {}, testcase = 0;
int dp[MAXN][MAXN][MAXN][MAXN];
int dfs(int p1, int p2, int p3, int p4, int state) {
	if(__builtin_popcount(state) == 5)
		return 0;
	if(used[p1][p2][p3][p4] == testcase)
		return dp[p1][p2][p3][p4];
	used[p1][p2][p3][p4] = testcase;
	int &ret = dp[p1][p2][p3][p4];
	int t, v;
	ret = 0;
	if(p1 < N) {
		t = pile[0][p1];
		v = (state>>t)&1;
		ret = max(ret, v + dfs(p1+1, p2, p3, p4, state^(1<<t)));
	}
	if(p2 < N) {
		t = pile[1][p2];
		v = (state>>t)&1;
		ret = max(ret, v + dfs(p1, p2+1, p3, p4, state^(1<<t)));
	}
	if(p3 < N) {
		t = pile[2][p3];
		v = (state>>t)&1;
		ret = max(ret, v + dfs(p1, p2, p3+1, p4, state^(1<<t)));
	}
	if(p4 < N) {
		t = pile[3][p4];
		v = (state>>t)&1;
		ret = max(ret, v + dfs(p1, p2, p3, p4+1, state^(1<<t)));
	}
	return ret;
}
int main() {
	while(scanf("%d", &N) == 1 && N) {
		for(int i = 0; i < N; i++)
			for(int j = 0; j < 4; j++)
				scanf("%d", &pile[j][i]);
		testcase++;
		int ret = dfs(0, 0, 0, 0, 0);
		printf("%d\n", ret);
	}
	return 0;
}
/*
5
1 2 3 4
1 5 6 7
2 3 3 3
4 9 8 6
8 7 2 1
1
1 2 3 4
3
1 2 3 4
5 6 7 8
1 2 3 4
0
*/
