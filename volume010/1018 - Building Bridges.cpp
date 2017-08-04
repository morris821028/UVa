#include <bits/stdc++.h>
using namespace std;

const int MAXN = 128;
char g[MAXN][MAXN];
int belong[MAXN][MAXN];
int n, m;

struct E {
	int u, v, c;
	E(int u=0, int v=0, int c=0):
		u(u), v(v), c(c) {}
	bool operator<(const E &o) const {
		return c < o.c;
	}
};

void dfs(int x, int y, int label) {
	if (x < 0 || y < 0 || x >= n || y >= m)
		return ;
	if (belong[x][y] || g[x][y] != '#')
		return ;
	belong[x][y] = label;
	dfs(x+1, y, label);
	dfs(x+1, y+1, label);
	dfs(x+1, y-1, label);
	
	dfs(x-1, y, label);
	dfs(x-1, y+1, label);
	dfs(x-1, y-1, label);
	
	dfs(x, y+1, label);
	dfs(x, y-1, label);
}

class DisjointSet {
public:
	int parent[MAXN*MAXN], weight[MAXN*MAXN];
	void init(int n) {
		for (int i = 0; i <= n; i++)
			parent[i] = i, weight[i] = 1;
	}
	int findp(int x) {
		return parent[x] == x ? x : (parent[x]=findp(parent[x]));
	}
	int joint(int x, int y) {
		x = findp(x), y = findp(y);
		if (x == y)	return 0;
		if (weight[x] > weight[y])
			parent[y] = x, weight[x] += weight[y];
		else
			parent[x] = y, weight[y] += weight[x];
		return 1;
	}
} D;

int main() {
	int cases = 0;
	while (scanf("%d %d", &n, &m) == 2 && n) {
		for (int i = 0; i < n; i++)
			scanf("%s", g[i]);
			
		memset(belong, 0, sizeof(belong));
		int label = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (g[i][j] == '#' && belong[i][j] == 0) {
					label++;
					dfs(i, j, label);
				}
			}
		}
		
//		for (int i = 0; i < n; i++) {
//			for (int j = 0; j < m; j++)
//				printf("%d ", belong[i][j]);
//			puts("");
//		}
//				
		vector<E> A;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (g[i][j] != '#')
					continue;
				int u = belong[i][j], v;
				int tx = i, ty = j+1, len = 1;
				while (ty < m && g[tx][ty] == '.') {
					if (ty+1 < m && g[tx][ty+1] == '#') {
						v = belong[tx][ty+1];
						A.push_back(E(u, v, len));
					}
					if (tx-1 >= 0 && ty+1 < m && g[tx-1][ty+1] == '#') {
						v = belong[tx-1][ty+1];
						A.push_back(E(u, v, len));
					}
					if (tx+1 < n && ty+1 < m && g[tx+1][ty+1] == '#') {
						v = belong[tx+1][ty+1];
						A.push_back(E(u, v, len));
					}
					len++, ty++;
				}
				
				tx = i+1, ty = j, len = 1;
				while (tx < n && g[tx][ty] == '.') {
					if (tx+1 < n && g[tx+1][ty] == '#') {
						v = belong[tx+1][ty];
						A.push_back(E(u, v, len));
					}
					if (tx+1 < n && ty-1 >= 0 && g[tx+1][ty-1] == '#') {
						v = belong[tx+1][ty-1];
						A.push_back(E(u, v, len));
					}
					if (tx+1 < n && ty+1 < m && g[tx+1][ty+1] == '#') {
						v = belong[tx+1][ty+1];
						A.push_back(E(u, v, len));
					}
					len++, tx++;
				}
			}
		}
				
		int ret = label, bridge = 0, cost = 0;
		// minimum spanning tree
		sort(A.begin(), A.end());
		D.init(label);
		for (int i = 0; i < A.size(); i++) {
			if (D.joint(A[i].u, A[i].v)) {
				bridge++, ret--, cost += A[i].c;
//				printf("%d %d %d\n", A[i].u, A[i].v, A[i].c);
			}
		}
		
		if (cases)
			puts("");
		printf("City %d\n", ++cases);
		if (bridge == 0 && ret == 1 || label == 0) {
			printf("No bridges are needed.\n");
		} else {
			if (bridge == 0)
				printf("No bridges are possible.\n");
			else if (bridge == 1)
				printf("%d bridge of total length %d\n", bridge, cost);
			else
				printf("%d bridges of total length %d\n", bridge, cost);
			if (ret != 1)
				printf("%d disconnected groups\n", ret);
		}
//		printf("%d\n", ret);
	}
	return 0;
}
/*
3 3
...
...
...
3 5
#...#
..#..
#...#
3 5
##...
.....
....#
3 5
#.###
#.#.#
###.#
3 5
#.#..
.....
....#
4 5
#.#..
.....
.....
...#.

4 5
#.#.#
.....
.....
.....
0 0
*/
