#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
const int MAXN = 65536;
vector<int> g[MAXN];
int visited[MAXN], vIdx, back[MAXN], depth[MAXN];
int visited2[MAXN];
long long ret = 0;
int N, M, x, y;

int tarjan(int u, int p, int component_sz) {
	back[u] = depth[u] = ++vIdx;
	visited[u] = 1;
	int son = 0, size = 1;
	int sum = 0;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (!visited[v]) {
			int sz = tarjan(v, u, component_sz);
			back[u] = min(back[u], back[v]);
			son++, size += sz;
			if (back[v] >= depth[u]) {
				ret += (long long) sz * (component_sz - sz - 1); // (up & other branch) -> (this branch)
				sum += sz;
			}
		} else if (v != p) {
			back[u] = min(back[u], depth[v]);
		}
	}
	 ret += (long long) sum * (component_sz - sum - 1); // (all branch) -> (up)
	return size;
}

int getComponentSize(int u) {
	visited2[u] = 1;
	int sz = 1;
	for (int i = 0; i < g[u].size(); i++) {
		if (!visited2[g[u][i]]) {
			sz += getComponentSize(g[u][i]);
		}
	}
	return sz;
}

int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++)
			g[i].clear();
		for (int i = 0; i < M; i++) {
			scanf("%d %d", &x, &y);
			x--, y--;
			g[x].push_back(y);
			g[y].push_back(x);
		}
		
		ret = 0;
		// find all cut point
		vIdx = 0;
		for (int i = 0; i < N; i++)
			visited[i] = visited2[i] = 0;
		for (int i = 0; i < N; i++) {
			if (!visited[i])
				tarjan(i, -1, getComponentSize(i));
		}
		
		printf("Case %d: %lld\n", ++cases, ret);
	}
    return 0;
}
/*
3
4 3
1 2
2 3
3 4

8 9
1 2
1 8
8 2
2 3
3 4
2 4
3 5
5 7
5 6

5 6
1 2
2 3
3 1
1 4
4 5
5 1
*/
/*
3
3 3
1 2
2 3
1 3

4 4
2 4
4 3
2 3
3 1

6 5
1 2
2 3
1 3
4 5
5 6
*/
