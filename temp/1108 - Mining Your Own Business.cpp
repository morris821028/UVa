#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

#define MAXN 65536
vector<int> g[MAXN];
int visited[MAXN], vIdx, back[MAXN], depth[MAXN];
int cutPoint[MAXN];
void tarjan(int u, int p, int root) {
	back[u] = depth[u] = ++vIdx;
	visited[u] = 1;
	int son = 0;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (!visited[v]) {
			tarjan(v, u, root);
			back[u] = min(back[u], back[v]);
			son++;
			if ((u == root && son > 1) || (u != root && back[v] >= depth[u]))
				cutPoint[u]++;
		} else if (v != p) {
			back[u] = min(back[u], depth[v]);
		}
	}
}
//
set<int> adjCutPt;
int comSize = 0;
void dfs(int u) {
	visited[u] = 1, comSize++;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (cutPoint[v])	adjCutPt.insert(v);
		if (cutPoint[v] || visited[v])
			continue;
		dfs(v);
	}
}
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out2.txt", "w+t", stdout); 
	int n, m, x, y;
	int cases = 0;
	while(scanf("%d", &m) == 1 && m) {
		int used[MAXN] = {}, usedn = 0;
		for (int i = 0; i < MAXN; i++)
			g[i].clear();
		n = 0;
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			n = max(n, max(x, y));
			x--, y--;
			used[x] = used[y] = 1;
			g[x].push_back(y);
			g[y].push_back(x);
		}
		for (int i = 0; i < n; i++)
			usedn += used[i];
		// find all cut point
		vIdx = 0;
		for (int i = 0; i < n; i++)
			visited[i] = cutPoint[i] = 0;
		for (int i = 0; i < n; i++) {
			if (!visited[i] && used[i])
				tarjan(i, -1, i);
		}
//		for (int i = 0; i < n; i++)
//			printf("%d ", cutPoint[i]);
//		puts("");
		// find each component adjacent one cut point, without any cut point.
		vector<int> D; 
		for (int i = 0; i < n; i++)
			visited[i] = 0;
		for (int i = 0; i < n; i++) {
			if (!visited[i] && !cutPoint[i]) {
				comSize = 0, adjCutPt.clear();
				dfs(i);
				if (adjCutPt.size() == 1)
					D.push_back(comSize);
			}
		}
		long long ways = 1, mn = D.size();
		for (int i = 0; i < D.size(); i++)
			ways *= D[i];
		if (D.size() == 0)	ways = (long long) usedn * (usedn-1) / 2, mn = 2;
		printf("Case %d: %lld %lld\n", ++cases, mn, ways);
	}
    return 0;
}
/*
3
1 2
2 3
3 1

32
15 15
8 4
17 7
6 1
12 6
3 17
5 9
20 8
20 4
7 15
4 18
7 17
14 1
14 3
5 3
5 18
13 18
5 15
1 13
18 3
2 4
20 4
20 16
5 20
2 3
10 4
6 6
13 16
2 7
6 17
14 14
1 15

33
10 12
17 14
19 3
2 3
19 9
17 16
9 2
8 9
6 8
14 10
3 13
14 4
9 3
1 18
10 7
15 14
13 1
15 1
16 6
14 20
12 7
6 17
19 5
19 1
10 13
5 3
18 6
12 17
4 5
9 18
9 17
9 20
15 15
*/

