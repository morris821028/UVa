#include <bits/stdc++.h>
using namespace std;
const int MAXN = 131072;
int parent[MAXN];
vector< pair<int, int> > bg[MAXN];
int findp(int x) {
	return parent[x] == x ? x : (parent[x] = findp(parent[x]));
}
void joint(int x, int y) {
	x = findp(x), y = findp(y);
	if (x > y)	swap(x, y);
	parent[x] = y;
}
int bfs(int st, int ed, int n) {
	static int dist[MAXN];
	for (int i = 0; i < n; i++)
		dist[i] = -1;
	queue<int> Q;
	int u, v;
	Q.push(st), dist[st] = 0;
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		if (u == ed)	return dist[ed];
		int l = 0, bptr = 0;
		while (l < n) {
			l = findp(l);
			while (bptr < bg[u].size() && bg[u][bptr].second < l) 
				bptr++;
			if (bptr < bg[u].size() && bg[u][bptr].first <= l) {
				l = bg[u][bptr].second+1;
				continue;
			}
			if (dist[l] == -1) {
				dist[l] = dist[u]+1;
				if (l-1 >= 0 && dist[l-1] != -1)
					joint(l-1, l);
				if (l+1 < n && dist[l+1] != -1)
					joint(l, l+1);
				Q.push(l);
			}
			l++;
		}
	}
	return -1;
}
int main() {
	int cases = 0;
	int testcase, n, m;
	int st, ed, l, r;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++) {
			parent[i] = i;
			bg[i].clear();
		}
		for (int i = 0; i < m; i++) {
			scanf("%d %d-%d", &st, &l, &r);
			bg[st].push_back(make_pair(l, r));
		}
		scanf("%d %d", &st, &ed);
		for (int i = 0; i < n; i++)
			sort(bg[i].begin(), bg[i].end());
		int ret = bfs(st, ed, n);
		printf("Case #%d: ", ++cases);
		if (ret == -1)
			puts("Impossible");
		else
			printf("%d\n", ret);
	}
	return 0;
}
/*
4
3
1
0 2-2
0 2
3
1
0 1-2
0 2
4
4
0 0-3
1 0-3
2 0-3
3 0-3
0 0
100000
3
0 1-99998
99999 1-50000
99999 50002-99999
0 1

5
100000
3
0 1-99998
99999 1-50000
99999 50002-99999
0 1
*/
