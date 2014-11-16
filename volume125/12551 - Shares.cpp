#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	int C, n, m;
	int x, s, q;
	int cost[512], profit[512];
	int cases = 0;
	while (scanf("%d", &C) == 1) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++)
			scanf("%d %d", &cost[i], &profit[i]), profit[i] -= cost[i];
		vector< pair<int, int> > items;
		for (int i = 0; i < m; i++) {
			scanf("%d", &x);
			int c = 0, p = 0;
			for (int j = 0; j < x; j++) {
				scanf("%d %d", &s, &q);
				c += cost[s] * q;
				p += profit[s] * q;
			}
			if (c <= C && p > 0)
				items.push_back(make_pair(c, p));
		}
		if (cases++)	puts("");
		if (items.size() == 0) {
			puts("0");
			continue;
		}
		if (items.size() == 1) {
			printf("%d\n", items[0].second);
			continue;
		}
		int g = C;
		for (int i = 0; i < items.size(); i++)
			g = __gcd(g, items[i].first);
		C /= g;
		for (int i = 0; i < items.size(); i++)
			items[i].first /= g;
		vector<int> dp(C + 1, 0);
		for (int i = 0; i < items.size(); i++) {
			for (int j = C; j >= items[i].first; j--)
				dp[j] = max(dp[j], dp[j - items[i].first] + items[i].second);
		}
		printf("%d\n", dp[C]);
	}
	return 0;
}
/*
500
4 6
10 15
8 6
20 15
12 12
3 1 6 2 7 3 8
3 3 8 1 10 2 4
3 4 10 2 5 1 10
2 1 4 2 4
1 3 2
2 4 3 2 1

200000000
5 30
2800 3500
1400 4800
2900 2800
500 3800
3300 4700
2 2 13 4 15
4 4 1 1 22 3 17 5 22
1 3 2
1 3 6
4 1 11 2 5 3 7 5 15
1 5 1
4 2 26 1 21 3 8 5 26
2 3 5 2 26
4 2 30 4 12 3 7 5 14
3 3 8 2 20 5 3
1 5 30
2 1 29 3 3
5 3 3 1 20 5 26 4 9 2 25
3 1 2 2 16 3 5
2 5 5 4 26
5 2 18 5 10 4 18 1 12 3 30
3 2 5 3 27 5 4
4 3 2 4 8 1 20 2 6
3 2 14 1 1 4 22
5 2 23 3 26 1 27 5 3 4 6
1 2 16
4 1 13 4 10 2 23 5 2
1 1 14
1 2 20
1 3 14
2 3 21 1 22
1 2 27
3 5 24 1 26 3 13
5 4 15 3 3 2 21 1 5 5 16
4 2 22 5 1 4 10 1 30
*/
