#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1024;
const int MOD = 1000000007;
int n, m;
int tree[MAXN];
int sum(int x) {
	int ret = 0;
	while (x > 0) {
		ret += tree[x];
		if (ret >= MOD)
			ret -= MOD;
		x -= x&(-x);
	}
	return ret;
}
void add(int x, int val, int n) {
	if (val == 0) 
		return;
	while (x <= n) {
		tree[x] += val;
		if (tree[x] >= MOD) 
			tree[x] -= MOD;
		x += x&(-x);
	}
}
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		static int a[MAXN], t[MAXN];
		int tn;

		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		tn = n;
		memcpy(t, a, sizeof(a[0])*n);
		sort(t, t+tn);
		tn = unique(t, t+tn)-t;
		for (int i = 0; i < n; i++)
			a[i] = (lower_bound(t, t+tn, a[i]) - t) + 1;

		static int dp[2][MAXN];
		memset(dp[0], 0, sizeof(dp[0][0])*(n+1));
		memset(dp[1], 0, sizeof(dp[1][0])*(n+1));
		for (int i = 0; i < n; i++)
			dp[0][i] = 1;
		for (int i = 1; i < m; i++) {
			memset(tree, 0, sizeof(tree[0])*(tn+1));
			for (int j = 0; j < i; j++) {
				dp[1][j] = 0;
				add(a[j], dp[0][j], tn);
			}
			for (int j = i; j < n; j++) {
				dp[1][j] = sum(a[j]-1);
				add(a[j], dp[0][j], tn);
			}
			memcpy(dp[0], dp[1], sizeof(dp[0][0])*n);
		}
		int ret = 0;
		for (int i = 0; i <= n; i++) {
			ret += dp[0][i];
			if (ret >= MOD)
				ret -= MOD;
		}
		printf("Case #%d: %d\n", ++cases, ret);
	}
	return 0;
}
/*
2
3 2
1 2 3
3 2
3 2 1
*/
