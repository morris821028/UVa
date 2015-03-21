// BCC
#include <stdio.h> 
#include <string.h>
#include <vector> 
#include <stack>
#include <algorithm>
using namespace std;
const int MAXN = 1024;
class BCC {
public:
	vector<int> g[MAXN], bcc[MAXN];
	stack< pair<int, int> > stk;
	int n;
	int vfind[MAXN], findIdx;
	int visited[MAXN];
	int bcc_tmp[MAXN], bccCnt, cutPt[MAXN];
	int dfs(int u, int p) {
		visited[u] = 1;
		vfind[u] = ++findIdx;
		
		int mn = vfind[u], branch = 0, t;
		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i];
			if (!visited[v]) {
				stk.push(make_pair(u, v));
				t = dfs(v, u);
				mn = min(mn, t), branch++;
				if (t >= vfind[u]) {
					pair<int, int> e;
					bcc[++bccCnt].clear();
					do {
						e = stk.top(), stk.pop();
						if (bcc_tmp[e.first] != bccCnt)
							bcc[bccCnt].push_back(e.first), bcc_tmp[e.first] = bccCnt;
						if (bcc_tmp[e.second] != bccCnt)
							bcc[bccCnt].push_back(e.second), bcc_tmp[e.second] = bccCnt;
					} while (e != make_pair(u, v));
					cutPt[u] = 1;
				}
			} else if (vfind[v] < vfind[u] && v != p) {
				stk.push(make_pair(u, v));
				mn = min(mn, vfind[v]);
			}
		}
		if (p < 0 && branch == 1)	cutPt[u] = 0;
		return mn;
	}
	void findBCC() {
		while (!stk.empty())	stk.pop();
        memset(visited, 0, sizeof(visited));
        memset(bcc_tmp, 0, sizeof(bcc_tmp));
        bccCnt = 0;
        for (int i = 0; i < n; i++) {
			if (!visited[i]) {
				findIdx = 0;
				dfs(i, -1);
			}
		}
	}
	void addEdge(int x, int y) {
		g[x].push_back(y), g[y].push_back(x);
	}
	void init(int n) {
		this->n = n;
		for (int i = 0; i < n; i++)
			g[i].clear();
	}
} g;

int A[MAXN][MAXN];
int belong[MAXN], color[MAXN];
int isBipartite(int u) {
	for (int i = 0; i < g.g[u].size(); i++) {
		int v = g.g[u][i];
		if (belong[u] != belong[v])	
			continue;
		if (color[v] == color[u])
			return false;
		if (!color[v]) {
			color[v] = 3 - color[u];
			if (!isBipartite(v))
				return false;
		}
	}
	return true;
}
int main() {
	int n, m, x, y;
	while (scanf("%d %d", &n, &m) == 2 && n) {
		memset(A, 0, sizeof(A));
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y), x--, y--;
			A[x][y] = A[y][x] = 1;
		}
		
		g.init(n);
		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++) {
				if (!A[i][j]) {
					g.addEdge(i, j);
//					printf("%d %d --\n", i, j);
				}
			}
		}
		
		g.findBCC();
		
		memset(belong, 0, sizeof(belong));
		int onOddCycle[MAXN] = {};
		for (int i = 1; i <= g.bccCnt; i++) {
			for (int j = 0; j < g.bcc[i].size(); j++) {
				belong[g.bcc[i][j]] = i, color[g.bcc[i][j]] = 0;
//				printf("%d ", g.bcc[i][j]);
			}
//			puts("");
			memset(color, 0, sizeof(color));
			color[g.bcc[i][0]] = 1;
			if (!isBipartite(g.bcc[i][0])) { // 
				for (int j = 0; j < g.bcc[i].size(); j++)
					onOddCycle[g.bcc[i][j]] = 1;
			}
		}
		
		int ret = n;
		for (int i = 0; i < n; i++)
			ret -= onOddCycle[i];
		printf("%d\n", ret);
	}
	return 0;
}
/*
7 9
1 2
2 3
3 1
1 4
4 5
5 1
1 6
6 7
7 1

4 5
1 2
2 3
3 4
4 1
2 4

4 4
1 2
2 3
3 1
1 4

5 5
1 4
1 5
2 5
3 4
4 5

12 3
8 7
2 3
4 2

7 12
4 7
5 6
1 7
2 1
1 3
2 7
5 1
6 3
6 7
3 7
3 4
4 1

0 0
*/
