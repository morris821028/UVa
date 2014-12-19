#include <stdio.h>
#include <string.h>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
#define MAXN 1024
vector<int> g[MAXN];
int visited[MAXN];
int SG[MAXN];
int dfsSG(int u) {
	if (visited[u])			return SG[u];
	if (g[u].size() == 0)	return SG[u] = 0;
	int &ret = SG[u];
	visited[u] = 1;
	map<int, int> mex;
	for (int i = 0, v; i < g[u].size(); i++) {
		v = g[u][i];
		mex[dfsSG(v)] = 1;
	}
	int last = -1;
	for (map<int, int>::iterator it = mex.begin();
		it != mex.end(); it++) {
		if (it->first > last + 1)
			return ret = (last + 1);
		last = it->first;
	}
	return ret = (last + 1);
}
int main() {
	int n, m, x, y, s;
	while (scanf("%d %d", &n, &m) == 2 && n) {
		for (int i = 0; i < n; i++)
			g[i].clear();
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			g[x].push_back(y);
		}
		
		memset(visited, 0, sizeof(visited));
		for (int i = 0; i < n; i++)
			dfsSG(i);
			
		int ret = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &s);
			if (s&1)
				ret ^= SG[i];
		}
		puts(ret ? "First" : "Second");
	}
	return 0;
}
/*
4 3
0 1
1 2
2 3
1
0
0
0

7 7
0 1
0 2
0 4
2 3
4 5
5 6
4 3
1
0
1
0
1
0
0

0 0
*/
