#include <bits/stdc++.h>
using namespace std;

const int MAXN = 405;
vector<pair<int, int>> g[MAXN];
int gw[MAXN][MAXN];
int n, m, delta;

int sssp(int st) {
	static int cost[MAXN][MAXN], inq[MAXN][MAXN];
	for (int i = 1; i <= n; i++) {
		memset(cost[i], 0x3f, sizeof(cost[0][0])*(n+1));
		memset(inq[i], 0, sizeof(inq[0][0])*(n+1));
	}
	queue<pair<int, int>> Q;
	for (auto e1 : g[st]) {
		int v = e1.first, h1 = e1.second;
		for (auto e2 : g[v]) {
			int x = e2.first, h2 = e2.second;
			int c = delta*2 + abs(h1 - h2);
			if (c < cost[x][v]) {
				cost[x][v] = c;
				if (!inq[x][v])
					Q.push({x, v}), inq[x][v] = 1;
			}
		}
	}
	while (!Q.empty()) {
		auto u = Q.front(); Q.pop();
		inq[u.first][u.second] = 0;
		const int h1 = gw[u.first][u.second];
		for (auto &e : g[u.first]) {
			int v = e.first, h2 = e.second;
			int c = cost[u.first][u.second] + abs(h1-h2) + delta;
			if (c < cost[v][u.first]) {
				cost[v][u.first] = c;
				if (!inq[v][u.first]) {
					inq[v][u.first] = 1;
					Q.push({v, u.first});
				}
			}
		}
	}
	
	int ret = INT_MAX;
	for (int i = 1; i <= n; i++) {
		if (i != st && g[i].size() == 1) {
			for (auto &e : g[i]) {
				if (cost[i][e.first] == 0x3f3f3f3f || e.first == st)
					continue;
//				printf("%d - %d %d\n", st, i, cost[i][e.first]);
				ret = min(ret, cost[i][e.first]);
			}
		}
	}
	return ret;
}

int main() {
	int testcase;
	int cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		cases++;
		scanf("%d %d %d", &m, &n, &delta);
		if (cases == 42)
			fprintf(stderr, "%d %d %d\n", m, n, delta);
		for (int i = 1; i <= n; i++)
			g[i].clear();
		memset(gw, -1, sizeof(gw));
		for (int i = 0; i < m; i++) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			g[u].emplace_back(v, w);
			g[v].emplace_back(u, w);
			assert(gw[u][v] == -1);
			gw[u][v] = gw[v][u] = w;
		}
		int ret = INT_MAX;
		for (int i = 1; i <= n; i++) {
			if (g[i].size() == 1)
				ret = min(ret, sssp(i));
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
2
8
9
25
1  2  1
8  9  10
7  8  9
1  4  2
4  5  20
1  3  9
3  5  9
5  6  8

6
6
21
1  2  1
1  4  2
4  5  20
1  3  9
3  5  9
5  6  8

1
12
297
216
289 33 610
1 253 70
167 27 414
186 11 335
275 32 228
182 220 670
33 139 497
130 179 462
90 268 554
89 129 202
104 120 900
139 120 258
*/
