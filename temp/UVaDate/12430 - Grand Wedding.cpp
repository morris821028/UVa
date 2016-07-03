// bipartite graph, binary search
#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
#include <algorithm>
using namespace std;
const int MAXN = 65536;
vector< pair<int, int> > g[MAXN];
int color[MAXN], visited[MAXN];
bool checkBipartite(int N, int limit) {
	vcases ++;
	int u, v;
	for (int i = 0; i < N; i++) {
		if (visited[i] == vcases)	continue;
		queue<int> Q;
		Q.push(i), color[i] = 1, visited[i] = vcases;
		while (!Q.empty()) {
			u = Q.front(), Q.pop();
			for (int i = 0; i < g[u].size(); i++) {
				if (g[u][i].second >= limit) // demolish
					continue;
				v = g[u][i].first;
				if (visited[v] != vcases) {
					color[v] = 1 - color[u], visited[v] = vcases;
					Q.push(v);
				} else {
					if (color[v] == color[u])
						return 0;
				}
			}
		}
	}
    return 1;
}

int main() {
	int testcase;
	int n, m, x, y, w;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		
		int mnw = 0x3f3f3f3f, mxw = 0;
		for (int i = 0; i < n; i++) 
			g[i].clear();		
			
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &x, &y, &w);
			x--, y--;
			g[x].push_back(make_pair(y, w));
			g[y].push_back(make_pair(x, w));
			mnw = min(mnw, w), mxw = max(mxw, w);
		}
		
		if (checkBipartite(n, 0x3f3f3f3f)) {
			puts("0");
			continue;
		}
		
		int l = mnw, r = mxw, mid, ret = mnw;
		while (l <= r) {
			mid = (l + r)/2;
			if (checkBipartite(n, mid))
				l = mid + 1, ret = mid;
			else
				r = mid - 1;
		}
		
		if (ret == mnw)
			puts("-1");
		else
			printf("%d\n", ret);
	}
	return 0;
}
/*
1
4 5
1 2 1
3 1 7
2 3 3
2 4 11
3 4 5
*/
