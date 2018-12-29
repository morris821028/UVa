#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;
struct Country {
	char name[30];
	int xl, xr, yl, yr;
	int cnt;
	int day;
} C[MAXN];

const int MAXX = 25;
const int MAXY = 25;
struct City {
	int coin[30], next[30];
	int cid;
	int cnt;
} g[MAXX][MAXY];

int simulate(int ts, int n) {
	int ret = 0;
	const int dx[] = {0, 0, 1, -1};
	const int dy[] = {1, -1, 0, 0};
	for (int i = 0; i < n; i++) {
	for (int p = C[i].xl; p <= C[i].xr; p++) {
		for (int q = C[i].yl; q <= C[i].yr; q++) {
			// export
			for (int j = 0; j < n; j++) {
				int give = g[p][q].coin[j] / 1000;
				if (give == 0)
					continue;
				int lost = 0;
				for (int k = 0; k < 4; k++) {
					int tx = p + dx[k];
					int ty = q + dy[k];
					if (g[tx][ty].cid < 0)
						continue;
					g[tx][ty].next[j] += give;
					lost += give;
				}
				g[p][q].coin[j] -= lost;
			}
		}
	}
	}

	for (int i = 0; i < n; i++) {
	for (int p = C[i].xl; p <= C[i].xr; p++) {
		for (int q = C[i].yl; q <= C[i].yr; q++) {
			// import
			for (int j = 0; j < n; j++) {
				if (g[p][q].next[j] == 0)
					continue;
				if (g[p][q].coin[j] == 0 && g[p][q].next[j] > 0) {
					g[p][q].cnt--;
					if (g[p][q].cnt == 0 && C[i].day < 0) {
						C[i].cnt--;
						if (C[i].cnt == 0)
							C[i].day = ts, ret++;
					}
				}
				g[p][q].coin[j] += g[p][q].next[j];
				g[p][q].next[j] = 0;
			}
		} 
	}
	}
	return ret;
}

int main() {
	int n;
	int cases = 0;
	while (scanf("%d", &n) == 1 && n) {
		memset(g, -1, sizeof(g));

		for (int i = 0; i < n; i++) {
			scanf("%s %d %d %d %d", &C[i].name, &C[i].xl, &C[i].yl, &C[i].xr, &C[i].yr);
			C[i].cnt = (C[i].xr-C[i].xl+1) * (C[i].yr-C[i].yl+1);
			C[i].day = -1;
			for (int p = C[i].xl; p <= C[i].xr; p++) {
				for (int q = C[i].yl; q <= C[i].yr; q++) {
					memset(g[p][q].coin, 0, sizeof(g[p][q].coin));
					memset(g[p][q].next, 0, sizeof(g[p][q].next));
					g[p][q].coin[i] = 1000000;
					g[p][q].cid = i;
					g[p][q].cnt = n-1;
					if (g[p][q].cnt == 0)
						C[i].cnt--, C[i].day = 0;
				} 
			}
		}

		int complete = n;
		for (int i = 0; i < n; i++)
			complete -= C[i].day >= 0;
		for (int t = 1; complete > 0; t++)
			complete -= simulate(t, n);

		vector<pair<int, string>> ret(n);
		for (int i = 0; i < n; i++)
			ret[i] = {C[i].day, C[i].name};
		sort(ret.begin(), ret.end());
		printf("Case Number %d\n", ++cases);
		for (int i = 0; i < n; i++)
			printf("   %s   %d\n", ret[i].second.c_str(), ret[i].first);
	}
	return 0;
}
/*
3
France 1 4 4 6
Spain 3 1 6 3
Portugal 1 1 2 2
1
Luxembourg 1 1 1 1
2
Netherlands 1 3 2 4
Belgium 1 1 2 2
0
*/
