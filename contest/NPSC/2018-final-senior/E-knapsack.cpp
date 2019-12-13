#include <bits/stdc++.h> 
using namespace std;

struct Item {
	int w, v, c;
	bool operator<(const Item &o) const {
		return w < o.w;
	}
};

int main() {
	int n;
	int m;
	Item items[2005];
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 1; i <= n; i++)
			assert(scanf("%d %d %d", &items[i].w, &items[i].v, &items[i].c) == 3);

		double ans = 0;
		static int dpBase[2005][10005] = {};
		for (int j = 1; j <= n; j++) {
			int w = items[j].w;
			int v = items[j].v;
			for (int k = 0; k <= m; k++) {
				dpBase[j][k] = dpBase[j-1][k];
				if (k >= w)
					dpBase[j][k] = max(dpBase[j][k], dpBase[j-1][k-w] + v);
			}
		}
		for (int i = 0; i <= m; i++)
			ans = max(ans, (double) dpBase[n][i]);
		for (int i = 1; i <= n; i++) {
			if (items[i].v <= items[i].c)
				continue;
			static int dp[10005];
			memcpy(dp, dpBase[i-1], sizeof(dp[0])*(m+1));
			for (int j = i+1; j <= n; j++) {
				int w = items[j].w;
				int v = items[j].v;
				for (int k = m; k >= w; k--)
					dp[k] = max(dp[k], dp[k-w] + v);
				int same = memcmp(dp, dpBase[j], sizeof(dp[0])*(m+1));
				if (same == 0) {
					memcpy(dp, dpBase[n], sizeof(dp[0])*(m+1));
					break;
				}
			}

			for (int j = 0; j <= m; j++) {
				double val = dp[j];
				if (m-j >= items[i].w) {
					val += items[i].v;
				} else {
					double cwv = (double) (m-j) / items[i].w * items[i].v - items[i].c;
					if (cwv > 0)
						val += cwv;
				} 
				ans = max(ans, val);
			}
		}
		printf("%.20lf\n", ans);
	}
	return 0;
}
/*
1 100
100 100 100
==> 100
2 1
100 3 10
100 5 20
==> 0
2 1
1 8562 3092
1 6283 5715
==> 8562
*/
