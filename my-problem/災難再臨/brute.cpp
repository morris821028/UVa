#include <stdio.h> 
#include <vector>
#include <queue>
#include <string.h>
#include <algorithm>
#include <assert.h>
using namespace std;
// http://oi.nks.edu.cn/showproblem?problem_id=2646 
#define MAXN 65536
#define LOGMAXN 17
vector<int> g[MAXN], invg[MAXN];
int test(int ban, int n) {
	int used[MAXN] = {};
	int u, v;
	queue<int> Q;
	used[ban] = 1;
	for (int i = 1; i <= n; i++) {
		if (g[i].size() == 0)
			Q.push(i), used[i] = 1;
	}
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		for (int i = 0; i < invg[u].size(); i++) {
			v = invg[u][i];
			if (used[v] == 0) {
				used[v] = 1;
				Q.push(v);
			}
		}
	}
	int bb = 0;
	for (int i = 1; i <= n; i++) {
		if (invg[i].size() == 0) {
			bb += used[i] == 0;
		}
	}
//	printf("[%d] %d\n", ban, bb);
	return bb;
}
int main() {
	freopen("in.txt", "r+t", stdin);
	freopen("out.txt", "w+t", stdout); 	
	int n, x, y, u, v;
	while(scanf("%d", &n) == 1) {
		for (int i = 0; i <= n; i++)
			g[i].clear(), invg[i].clear();
		for (int i = 1; i <= n; i++) {
			while (scanf("%d", &x) == 1 && x) {
				g[i].push_back(x);
				invg[x].push_back(i);
			}
		}
		int ret = 0, mx = 0;
		for (int i = 1; i <= n; i++) {
			if (invg[i].size() == 0) // start point
				continue;
			if (g[i].size() == 0) // end point
				continue;
			int t = test(i, n);
			if (t > 0) {
				ret++;
				mx = max(mx, t);
			}
		}
		printf("%d %d\n", ret, mx);
	}
	return 0;
}
/*
17
10 13 0
9 12 0
9 14 11 0
10 0
12 0
17 0
0
0
13 14 0
11 0
15 0
15 0
16 0
7 0
16 0
17 0
8 0 
*/
