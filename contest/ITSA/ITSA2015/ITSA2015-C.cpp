#include <stdio.h> 
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int MAXN = 32767;
vector<int> g[MAXN];
int deg[MAXN], dist[MAXN];

int main() {
	int testcase, n, u, v;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			g[i].clear(), deg[i] = 0, dist[i] = -1;
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &u, &v);
			g[u].push_back(v);
			g[v].push_back(u);
			deg[u]++, deg[v]++;
		}
		
		queue<int> Q;
		for (int i = 0; i < n; i++)
			if (deg[i] == 1)
				Q.push(i), dist[i] = 1;
		while (!Q.empty()) {
			u = Q.front(), Q.pop();
			for (int i = 0; i < g[u].size(); i++) {
				v = g[u][i];
				if (--deg[v] == 1) {
					dist[v] = dist[u] + 1;
					Q.push(v);
				}
			}
		}
		
		int mx = 0, ret;
		for (int i = 0; i < n; i++) {
			if (dist[i] > mx)
				mx = dist[i], ret = i;
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
2
5
0 1
1 2
1 3
3 4
8
0 2
1 2
2 3
3 4
3 5
5 6
6 7 
*/
