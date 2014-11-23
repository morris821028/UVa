#include <stdio.h>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
struct Rectangle {
	int lx, ly, rx, ry;
	void read() {
		scanf("%d %d %d %d", &lx, &ly, &rx, &ry);
	}
	int contain(Rectangle &a) {
		return lx <= a.lx && ly <= a.ly && rx >= a.rx && ry >= a.ry;
	}
	int contain(int x, int y) {
		return lx <= x && ly <= y && rx >= x && ry >= y;
	}
} rect[32767];
struct QPt {
	int x, y, label;
	QPt(int a = 0, int b = 0, int c = 0):
		x(a), y(b), label(c) {}
	bool operator<(const QPt &a) const {
		return make_pair(x, y) < make_pair(a.x, a.y);
	}
};
vector<int> g[32767], tree[32767];
int parent[32767], visited[32767], dp[32767];
void dfs(int u) {
	visited[u] = 1;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (visited[v] == 0)
			dfs(v);
		if (dp[v] + 1 > dp[u])
			dp[u] = dp[v] + 1, parent[u] = v;
	}
}
int search(int u, int x, int y) {
	for (int i = 0; i < tree[u].size(); i++) {
		int v = tree[u][i];
		if (rect[v].contain(x, y))
			return search(v, x, y);
	}
	return u;
}
int main() {	
	freopen("in.txt", "r+t", stdin);
	freopen("brute_out.txt", "w+t", stdout); 
	int n, m, x, y;
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++) {
			rect[i].read(), g[i].clear();
			dp[i] = 0, parent[i] = -1;
			tree[i].clear();
			visited[i] = 0;
		}
		scanf("%d", &m);
		vector<QPt> XY;
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			XY.push_back(QPt(x, y, i));
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j)	continue;
				if (rect[i].contain(rect[j])) {
					g[j].push_back(i);
				}
			}
		}
		int indeg[32767] = {};
		for (int i = 0; i < n; i++) {
			if (visited[i] == 0)
				dfs(i);
		}
		for (int i = 0; i < n; i++)
			printf("%d%c", dp[i] + 1, i == n - 1 ? '\n' : ' ');
		
		vector<int> root;
		for (int i = 0; i < n; i++) {
			if (parent[i] != -1)
				tree[parent[i]].push_back(i);
			else
				root.push_back(i);
		}
		for (int i = 0; i < m; i++) {
			int ok = 0;
			for (int j = 0; j < root.size(); j++)
				if (rect[root[j]].contain(XY[i].x, XY[i].y)) {
					printf("%d\n", search(root[j], XY[i].x, XY[i].y));
					ok = 1;
					break;
				}
			if (!ok)
				puts("-1");
		}
	}
	return 0;
}
/*
7
0 0 10 10
1 1 9 2
1 3 9 7
2 4 4 6
5 4 6 5
7 5 8 6
1 8 9 9 
6 
3 5
6 6
7 4
9 1 
2 4 
-1 -1 
*/ 
