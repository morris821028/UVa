#include <stdio.h> 
#include <vector>
#include <algorithm>
using namespace std;

vector<int> g[1024];
int n, m, s, x, y;
int ret = 0;
int dfs(int u, int p, int dep, int &place) {
	int leaf = 0, pp = 0x3f3f3f3f;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (v == p)
			continue;
		int p;
		int tmp = dfs(v, u, dep + 1, p);
		pp = min(p, pp);
		leaf = max(leaf, tmp);
	}
	place = pp;
	if (leaf - dep + pp - dep <= m)
		leaf = 0;
	if (leaf == dep + m) {
		place = dep;
		ret += (u != s), leaf = 0/*, printf("place %d, %d\n", u, place)*/;
	}
	if (g[u].size() == 1)
		return dep;
	else
		return leaf;
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d", &n, &s, &m);
		for (int i = 0; i <= n; i++)
			g[i].clear();
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &x, &y);
			g[x].push_back(y);
			g[y].push_back(x);
		}
		
		ret = 0;
		int foo;
		dfs(s, -1, 0, foo);
		printf("%d\n", ret);
	}
	return 0;
}
/*
2 
14 12 2 
1 2 
2 3 
3 4 
4 5 
5 6 
7 5 
8 5 
4 9 
10 3 
2 12 
12 14 
13 14 
14 11 

14 3 4 
1 2 
2 3 
3 4 
4 5 
5 6 
7 5 
8 5 
4 9 
10 3 
2 12 
12 14 
13 14 
14 11
*/
