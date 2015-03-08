#include <stdio.h>
#define MAXN 1048576
int N, d, s, a;
double dp[MAXN];
int used[MAXN], cases = 0;
// E[1] = (E[0] + E[2] + a + s)/2
// E[2] = E[1] + d
// E[1] = (E[0] + E[1] + a + s + d)/2
// E[1] = E[0] + a + s + d = a + s + d
double dfs(int N) {
	if (N == 1)				return (d + s + a);
	if (used[N] == cases)	return dp[N];
	double &ret = dp[N];
	used[N] = cases, ret = 0;
	if (N&1) {
		ret = (dfs(N+1) + a)/2 + (dfs(N-1) + s)/2;
	} else {
		ret = dfs(N/2) + d;
	} 
	return ret;
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d %d", &N, &d, &s, &a);
		++cases;
		printf("%.3lf\n", dfs(N));
	}
	return 0;
}
