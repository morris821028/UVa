#include <stdio.h>
#include <string.h>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int indeg[512], outdeg[512], mg[512][512];
vector<int> g[512];
int check(int st, int banu, int banv, int n) {
	queue<int> Q;
	int in[512], out[512], visited = 0, u, v;
	for(int i = 0; i < n; i++)
		in[i] = indeg[i], out[i] = outdeg[i];
	Q.push(st), in[banv]--, out[banu]--;
	while(!Q.empty()) {
		u = Q.front(), Q.pop();
		visited++;
		for(int i = 0; i < g[u].size(); i++) {
			v = g[u][i];
			if(--in[v] == 0)
				Q.push(v);
		}
		if(Q.size() > 1)	return 0;
	}
	return visited == n && mg[u][st];
}
int main() {
	int testcase, n, m, u, v;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &n, &m);
		memset(mg, 0, sizeof(mg));
		memset(indeg, 0, sizeof(indeg));
		memset(outdeg, 0, sizeof(outdeg));
		for(int i = 0; i < n; i++)
			g[i].clear();
		for(int i = 0; i < m; i++) {
			scanf("%d %d", &u, &v);
			mg[u][v] = 1;
			g[u].push_back(v);
			indeg[v]++, outdeg[u]++;
		}
		int ret = 0;
		for(int i = 0; i < n && !ret; i++) {
			for(int j = 0; j < g[i].size() && !ret; j++) {
				u = i, v = g[i][j];
				if(indeg[v] == 1 && outdeg[u] == 1) {
					ret |= check(v, u, v, n);
				}
			}
		}
//		puts(ret ? "YES" : "NO");
		puts(ret ? "Yeah, I'm superman" : "Your DAGy was initially defected!");
	}
	return 0;
}
/*
5 6
0 1
1 2
2 3
3 4
4 0
1 3
*/
