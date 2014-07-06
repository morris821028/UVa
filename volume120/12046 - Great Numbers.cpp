#include <stdio.h>
int dp[45][2][3][4][5][6][1<<6];
int used[45][2][3][4][5][6][1<<6];
int dfs(int n, int m2, int m3, int m4, int m5, int m6, int mark) {
	if(n == 0) {
		int f = 1;
		if(mark&2)	f &= m2 == 0;
		if(mark&4)	f &= m3 == 0;
		if(mark&8)	f &= m4 == 0;
		if(mark&16)	f &= m5 == 0;
		if(mark&32)	f &= m6== 0;
		return f;
	}
	if(used[n][m2][m3][m4][m5][m6][mark])
		return dp[n][m2][m3][m4][m5][m6][mark];
	used[n][m2][m3][m4][m5][m6][mark] = 1;
	int& ret = dp[n][m2][m3][m4][m5][m6][mark];
	ret = 0;
	int t2, t3, t4, t5, t6;
	for(int i = 1; i <= 6; i++) {
		t2 = (m2 * 10 + i)%2;
		t3 = (m3 * 10 + i)%3;
		t4 = (m4 * 10 + i)%4;
		t5 = (m5 * 10 + i)%5;
		t6 = (m6 * 10 + i)%6;
		ret += dfs(n-1, t2, t3, t4, t5, t6, mark|(1<<(i-1)));
		ret %= 1000007;
	}
	return ret;
}
int main() {
	int testcase, n;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &n);
		printf("%d\n", dfs(n, 0, 0, 0, 0, 0, 0));
	}
	return 0;
}
