#include <bits/stdc++.h>
using namespace std;

const int MAXL = 4005;
const int MAXN = 1005;
int64_t dp[MAXL][3];
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
		for (int i = 0; i < n; i++)
			stick[i].a <<= 1;
		sort(stick, stick+n);

		memset(dp, 0, sizeof(dp));
		for (int i = 0, sum = 0; i < n; i++) {
			int f = stick[i].a, h = stick[i].a>>1, v = stick[i].v;
			sum = min(sum+f, l);
			for (int j = sum; j >= f; j--) {
				dp[j][0] = max(dp[j][0], dp[j-f][0]+v);
				dp[j][1] = max(dp[j][1], dp[j-h][0]+v);
				dp[j][1] = max(dp[j][1], dp[j-f][1]+v);
				dp[j][2] = max(dp[j][2], dp[j-h][1]+v);
				dp[j][2] = max(dp[j][2], dp[j-f][2]+v);
			}
			for (int j = min(sum, f-1); j >= h; j--) {
				dp[j][1] = max(dp[j][1], dp[j-h][0]+v);
				dp[j][2] = max(dp[j][2], dp[j-h][1]+v);
			}
		}

		int64_t ret = 0;
		for (int i = 0; i < n; i++)
			ret = max(ret, (int64_t) stick[i].v);
		for (int i = l; i >= 0; i--) {
			ret = max(ret, dp[i][0]);
			ret = max(ret, dp[i][1]);
			ret = max(ret, dp[i][2]);
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
