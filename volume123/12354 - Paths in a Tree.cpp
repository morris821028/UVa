#include <bits/stdc++.h> 
using namespace std;
const int MAXN = 20005;
vector<pair<int, int>> g[MAXN];
struct Stat {
	int upath, dpath, sum;
	Stat(int upath=0, int dpath=0, int sum=0):
		upath(upath), dpath(dpath), sum(sum) {}
};
Stat dfs(int u, int p) {
	int upath = 0, dpath = 0, sum = 0;
	for (auto e : g[u]) {
		int v = e.first;
		if (v == p)
			continue;
		Stat stat = dfs(v, u);
		if (e.second == 1) {
			sum += stat.dpath + stat.sum;
			upath += max(1, stat.upath);
		} else {
			sum += stat.upath + stat.sum;
			dpath += max(1, stat.dpath);
		}
	}
	int inner = min(upath, dpath);
	sum += inner;
	upath -= inner, dpath -= inner;
	return Stat(upath, dpath, sum);
}
int main() {
	int testcase, cases = 0, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			g[i].clear();
		for (int i = 1; i < n; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			g[u].push_back({v, 1});
			g[v].push_back({u, 0});
		}
		Stat ret = dfs(0, -1);
		int paths = ret.sum + ret.upath + ret.dpath - min(ret.upath, ret.dpath);
		printf("Case %d: %d\n", ++cases, paths);
	}
	return 0;
}
/*
2
4
0 1
1 2
1 3
5
0 1
1 2
1 3
0 4

1
10
0 1
2 0
1 3
4 2
5 1
0 6
7 4
0 8
9 2
*/
