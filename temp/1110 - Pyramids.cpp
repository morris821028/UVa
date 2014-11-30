#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
char dp[325][1048576];
#define MAXN 1000000
struct E {
	int w, sz, ssz;
	E(int a = 0, int b = 0, int c = 0):
		w(a), sz(b), ssz(c) {}
	bool operator<(const E &a) const {
		if (w != a.w)	return w < a.w;
		return ssz > a.ssz;
	}
};
E D[1024];
int main() {
	memset(dp, 0x70, sizeof(dp));
	int n, m = 0, cases = 0;
	int t1 = 3, t2 = 4, t3 = 2;
	int c1 = 10, c2 = 20, c3 = 5;
	int mx = 0;
	for (; c1 <= MAXN; ) {
		D[m++] = E(c1, t1 + 10000, t1);
		t1 += 2;
		c1 += t1 * t1;
	}
	for (; c2 <= MAXN; ) {
		D[m++] = E(c2, t2 + 10000, t2);
		t2 += 2;
		c2 += t2 * t2;
	}
	for (; c3 <= MAXN; ) {
		D[m++] = E(c3, t3, t3);
		t3 ++;
		c3 += t3 * t3;
	}
	sort(D, D + m);
	dp[0][0] = 0;
	for (int i = 0; i < m; i++) {
		for (int j = D[i].w; j <= MAXN; j++)
			dp[i+1][j] = dp[i][j-D[i].w] + 1;
		for (int j = 0; j <= MAXN; j++)
			dp[i+1][j] = min(dp[i+1][j], dp[i][j]);
	}	
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	while (scanf("%d", &n) == 1 && n) {
		printf("Case %d: ", ++cases);
		if (dp[m][n] >= 0x70) {
			puts("impossible");
		} else {
			vector<int> ret;
			int pre = m;
			for (int i = m-1; i >= 0; i--) { 
				if (D[i].w <= n && dp[i][n - D[i].w] + 1 == dp[pre][n]) {
					ret.push_back(D[i].sz);
					n -= D[i].w, pre = i;
				}
			} 
			for (int i = 0; i < ret.size(); i++) {
				if (ret[i] >= 10000)
					printf("%dL", ret[i] - 10000);
				else
					printf("%dH", ret[i]);
				if (i != ret.size() - 1)
					printf(" ");
				else
					puts("");
			}
		}
	}
	return 0;
}
/*
65
79
150
*/
