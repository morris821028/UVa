#include <bits/stdc++.h>
using namespace std;

const int MAXL = 4005;
const int MAXN = 1005;
int64_t dp[3][MAXL];
struct Stick {
	int a, v;
	Stick() {}
	Stick(int a, int v): a(a), v(v) {}
	bool operator<(const Stick &x) const {
		return a < x.a;
	}
} stick[MAXN];
int main() {
	int testcase, cases = 0;
	int n, l;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &l);
		for (int i = 0; i < n; i++)
			scanf("%d %d", &stick[i].a, &stick[i].v);

		l *= 2;
		sort(stick, stick+n);
		for (int i = 0; i < 3; i++)
			memset(dp[i], 0, sizeof(dp[0][0])*(l+1));	
		for (int i = 0, sum = 0; i < n; i++) {
			int f = stick[i].a<<1, h = stick[i].a, v = stick[i].v;
			sum = min(sum+f, l);
			for (int j = sum; j >= f; j--) {
				dp[0][j] = max(dp[0][j], dp[0][j-f]+v);
				dp[1][j] = max(dp[1][j], dp[0][j-h]+v);
				dp[1][j] = max(dp[1][j], dp[1][j-f]+v);
				dp[2][j] = max(dp[2][j], dp[1][j-h]+v);
				dp[2][j] = max(dp[2][j], dp[2][j-f]+v);
			}
			for (int j = min(sum, f-1); j >= h; j--) {
				dp[1][j] = max(dp[1][j], dp[0][j-h]+v);
				dp[2][j] = max(dp[2][j], dp[1][j-h]+v);
			}
		}

		int64_t ret = 0;
		for (int i = 0; i < n; i++)
			ret = max(ret, (int64_t) stick[i].v);
		for (int i = l; i >= 0; i--) {
			ret = max(ret, dp[0][i]);
			ret = max(ret, dp[1][i]);
			ret = max(ret, dp[2][i]);
		}
		printf("Case #%d: %lld\n", ++cases, ret);
	}
	return 0;
}
/*
4

3 7
4 1
2 1
8 1

3 7
4 2
2 1
8 4

3 5
4 1
2 2
8 9

1 1
10 3
*/
