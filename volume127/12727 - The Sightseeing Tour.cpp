#include <bits/stdc++.h>
using namespace std;
const int MAXM = 32;
struct bin {
	int a, b, c;
	bin(int a=0, int b=0, int c=0):
		a(a), b(b), c(c) {}
	bool operator<(const bin &x) const {
		if (b != x.b)	return b < x.b;
		return a < x.a;
	}
} B[MAXM];
int n, m, k;
int cost[305];
void dfs(int r, int l, int idx, int c) {
	if (r == n) {
		cost[c] = 1;
		return;
	}
	for (int i = idx; i < m; i++) {
		if (B[i].a <= r+1 && B[i].a > l && B[i].b > r)
			dfs(B[i].b, r+1, i+1, c+B[i].c);
	}
}
int64_t f(int x) {
	if (x <= 300)
		return cost[x];
	return cost[300] + (int64_t) (x-300)*(cost[300]-cost[299]);
}
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d", &n, &m, &k);
		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);
			B[i] = bin(a, b, c);
		}

		sort(B, B+m);
		memset(cost, 0, sizeof(cost));
		dfs(0, 0, 0, 0);

		for (int i = 1, prev = 0; i <= 300; i++) {
			if (cost[i] == 1) {
				prev = i;
				cost[i] = cost[i-1] + i;
			} else {
				cost[i] = cost[i-1] + prev;
			}
		}
		int64_t ret = 0;
		for (int i = 0; i < k; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			ret += f(y) - f(x-1);
		}
		printf("Case #%d: %lld\n", ++cases, ret);
	}
	return 0;
}
/*
2
3 4 2
1 1 4
1 2 1
2 3 2
3 3 1
1 3
10 10
5 6 2
1 2 5
2 2 1
3 5 10
3 4 10
4 5 10
5 5 5
12 17
23 26
*/
