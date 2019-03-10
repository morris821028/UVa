/*
一次把 DFS, BFS, Backtracking, Heuristic, Reduction 奉上

求在二維方格內不重複走訪點的情況連續走訪三次，尋求避開障礙物，並求出最大獲利總額。

在不重複走訪限制下，光一條路徑就是 NP，但可以派上插頭 DP 來解決一條的情況。但三條的狀態會讓內存爆炸，只剩下數學解和暴力搜索解。

過程中找到所有可行的割邊，把死胡同全部堵上，防止死胡同造成啟發函數估計不夠精準。接著考慮稠密和稀疏圖造成的搜索空間爆炸，不斷地從當前起點尋覓下一個獲利點，然後回溯回去接上路徑，然後再深入搜索下去。

然而，這樣還偷渡不過去。設想平面圖的性質，應該可以拆分成路徑組合一條和二條的搜索吧，好這樣貪心下去並且限制搜索次數，終於壓到秒數內，以 Rank 1 的效能過了 ...

看到參考解答也吐出不正確的答案，何必努力呢 ...

I guess that this problem is very tricky to find the optimal solution. 
Intuitively, the best solution needs to combine DFS, BFS, Backtracking, 
Heuristic and Reduction concepts. But, search space is still large for
three paths together. We can try to find the local maximum path for one
path. And then, compute others individually. So, the solution which
uDebug given can not provide correct answer for some cases, so am I.
But, you still pass the UVa OJ by this way.

It is not a correct solution. But Accepted 0.000 on UVa Online Judge.
*/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 11;
int8_t g[MAXN][MAXN], ng[MAXN][MAXN];
int n;

int8_t used[3][MAXN][MAXN] = {};
int ret = 0;
static const int dx[] = {0, 1, 0, -1};
static const int dy[] = {1, 0, -1, 0};

namespace SCC {

int vfind[MAXN*MAXN], findIdx;
int stk[MAXN*MAXN], stkIdx;
int in_stk[MAXN*MAXN], visited[MAXN*MAXN];
vector<tuple<int, int, int>> dead;

int find_bridge(int u, int p, int st) {
	in_stk[u] = visited[u] = 1;
	stk[++stkIdx] = u, vfind[u] = ++findIdx;
	int x = u/n, y = u%n;
	int mn = vfind[u];
	for (int i = 0; i < 4; i++) {
		int tx = x + dx[i];
		int ty = y + dy[i];
		if (tx < 0 || ty < 0 || tx >= n || ty >= n || g[tx][ty] == 2)
			continue;
		int v = tx*n + ty, d = 0x3f3f3f3f;
		if (!visited[v]) {
			d = find_bridge(v, u, st);
//			printf("%d %d, %d %d, %d %d\n", x, y, tx, ty, d, vfind[u]);
			if (d >= vfind[u]) {
//				puts("cuttttttt");
				do {
					assert(stkIdx >= 0);
					if (u != st) {
						int rm = stk[stkIdx];
						in_stk[rm] = 0;
						dead.push_back(make_tuple(rm/n, rm%n, g[rm/n][rm%n]));
//						printf("rm %d %d %d %d\n", rm/n, rm%n, rm, u);
					}
				} while (stkIdx >= 0 && stk[stkIdx--] != v);
			}
		} else {
			if (v != p && in_stk[v])
				d = vfind[v];
		}
		mn = min(mn, d);
	}
	if (x == n-1 && y == n-1)
		mn = min(mn, vfind[st]);
//	printf("--- back %d %d, %d %d\n", x, y, mn, vfind[u]);
	return mn;
}

vector<tuple<int, int, int>> remove_dead(int sx, int sy) {
	dead.clear();
	for (int i = 0; i < n*n; i++)
		visited[i] = in_stk[i] = vfind[i] = 0;
	stkIdx = findIdx = 0;
	int st = sx*n + sy;
	find_bridge(st, -1, st);
	for (auto e : dead)
		g[get<0>(e)][get<1>(e)] = 2;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (vfind[i*n+j] == 0 && g[i][j] != 2) {
				dead.push_back(make_tuple(i, j, g[i][j]));
				g[i][j] = 2;
			}
		}
	}
	return dead;
}
}

int h(int k, int x, int y) {
	int total = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			total += g[i][j] == 1;
	}
	if (k < 2)
		return total;
	static int Q[MAXN*MAXN][2];
	int8_t visited[MAXN][MAXN] = {};
	int qidx = 0, s = 0;
	Q[qidx][0] = x, Q[qidx][1] = y, qidx++, visited[x][y] = 1;
	for (int i = 0; i < qidx; i++) {
		x = Q[i][0], y = Q[i][1];
		s += g[x][y] == 1;
		if (x+1 < n && !visited[x+1][y] && !used[k][x+1][y] && g[x+1][y] != 2) {
			Q[qidx][0] = x+1, Q[qidx][1] = y, qidx++, visited[x+1][y] = 1;
		}
		if (x > 0 && !visited[x-1][y] && !used[k][x-1][y] && g[x-1][y] != 2) {
			Q[qidx][0] = x-1, Q[qidx][1] = y, qidx++, visited[x-1][y] = 1;
		}
		if (y+1 < n && !visited[x][y+1] && !used[k][x][y+1] && g[x][y+1] != 2) {
			Q[qidx][0] = x, Q[qidx][1] = y+1, qidx++, visited[x][y+1] = 1;
		}
		if (y > 0 && !visited[x][y-1] && !used[k][x][y-1] && g[x][y-1] != 2) {
			Q[qidx][0] = x, Q[qidx][1] = y-1, qidx++, visited[x][y-1] = 1;
		}
	}
	return s;
}

int possible(int k, int x, int y) {
	if (g[x][y] == 2)
		return 0;
	static int Q[MAXN*MAXN][2];
	int8_t visited[MAXN][MAXN] = {};
	int qidx = 0;
	Q[qidx][0] = x, Q[qidx][1] = y, qidx++, visited[x][y] = 1;
	for (int i = 0; i < qidx; i++) {
		x = Q[i][0], y = Q[i][1];
		if (x == n-1 && y == n-1)
			return 1;
		if (x+1 < n && !visited[x+1][y] && !used[k][x+1][y] && g[x+1][y] != 2) {
			Q[qidx][0] = x+1, Q[qidx][1] = y, qidx++, visited[x+1][y] = 1;
		}
		if (x > 0 && !visited[x-1][y] && !used[k][x-1][y] && g[x-1][y] != 2) {
			Q[qidx][0] = x-1, Q[qidx][1] = y, qidx++, visited[x-1][y] = 1;
		}
		if (y+1 < n && !visited[x][y+1] && !used[k][x][y+1] && g[x][y+1] != 2) {
			Q[qidx][0] = x, Q[qidx][1] = y+1, qidx++, visited[x][y+1] = 1;
		}
		if (y > 0 && !visited[x][y-1] && !used[k][x][y-1] && g[x][y-1] != 2) {
			Q[qidx][0] = x, Q[qidx][1] = y-1, qidx++, visited[x][y-1] = 1;
		}
	}
	return 0;
}

void dfs(int, int, int, int, int);

void find_path(int k, int x, int y, int ex, int ey, int s, int sx, int sy, int8_t dist[][MAXN], int &f) {
//	if (f)
//		return;
	int d = dist[x][y];
	for (int i = 3; i >= 0; i--) {
		int tx = x + dx[i];
		int ty = y + dy[i];
		if (tx < 0 || ty < 0 || tx >= n || ty >= n)
			continue;
		if (dist[tx][ty] != d-1)
			continue;
		if (tx == sx && ty == sy) {
			assert(g[sx][sy] == 0 && g[ex][ey] == 0);
			dfs(k, ex, ey, 0, s+1);
			f = 1;
			continue;
		}
		if (used[k][tx][ty] || g[tx][ty] != 0)
			continue;
		used[k][tx][ty] = 1;
		find_path(k, tx, ty, ex, ey, s, sx, sy, dist, f);
		used[k][tx][ty] = 0;
	}
}

void find_next(int k, int sx, int sy, int s) {
	queue<int> X, Y;
	int x = sx, y = sy;
	int8_t dist[MAXN][MAXN] = {};
	X.push(x), Y.push(y), dist[x][y] = 1;
	int has = 0, find_end = 0;
	while (!X.empty()) {
		x = X.front(); X.pop();
		y = Y.front(); Y.pop();
		for (int i = 3; i >= 0; i--) {
			int tx = x + dx[i];
			int ty = y + dy[i];
			if (tx < 0 || ty < 0 || tx >= n || ty >= n)
				continue;
			if (dist[tx][ty] || used[k][tx][ty] || g[tx][ty] == 2)
				continue;
			if (tx == n-1 && ty == n-1)
				find_end = 1;
			dist[tx][ty] = dist[x][y]+1;
			if (g[tx][ty] == 1) {
				has = 1;
				g[tx][ty] = 0, used[k][tx][ty] = 1;
				int f = 0;
//				printf("find path %d %d -> %d %d\n", sx, sy, tx, ty);
				find_path(k, tx, ty, tx, ty, s, sx, sy, dist, f);
				g[tx][ty] = 1, used[k][tx][ty] = 0;
			} else {
				X.push(tx), Y.push(ty);
			}
		}
	}
	if (find_end) {
		if (k < 2)
			dfs(k+1, 0, 0, 0, s);
	}
}


int test = 0;
int limit_k;
void dfs(int k, int x, int y, int d, int s) {
	if (test-- < 0)
		return;
	if (k >= limit_k)
		return;
	if (s >= ret) {
		if (!possible(k, x, y))
			return;
//		if (s > ret) {
//			printf("%d %d\n", k, ret);
//			for (int it = 0; it <= k; it++) {
//			for (int i = 0; i < n; i++) {
//				for (int j = 0; j < n; j++) {
//					if (k == it && i == x && j == y)
//						printf(" v");
//					else if (used[it][i][j] == 1)
//						printf(" x");
//					else
//						printf(" %d", g[i][j]);
//				}
//				puts("");
//			}
//			puts("////");
//			}
//		}
		if (s > ret) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (used[k][i][j] == 1) {
						ng[i][j] = 0;
					} else {
						ng[i][j] = g[i][j];
					}
				}
			}
			ret = s;
		}
	}
	
	if (s + h(k, x, y) <= ret)
		return;
	if (x == n-1 && y == n-1 && k < 2) {
		dfs(k+1, 0, 0, 0, s);
		return;
	}
//	if (ret >= 0) {
//		printf("try %d, %d\n", s, h(k, x, y));
//		for (int it = 0; it <= k; it++) {
//		for (int i = 0; i < n; i++) {
//			for (int j = 0; j < n; j++) {
//				if (i == x && j == y && it == k)
//					printf(" v");
//				else if (used[it][i][j] == 1)
//					printf(" x");
//				else
//					printf(" %d", g[i][j]);
//			}
//			puts("");
//		}
//		puts("////");
//		}
//		getchar();
//	}
	vector<tuple<int, int, int>> cover;
	if (k == 2)
		cover = SCC::remove_dead(x, y);
	used[k][x][y] = 1;
	find_next(k, x, y, s);
	used[k][x][y] = 0;
	for (auto e : cover)
		g[get<0>(e)][get<1>(e)] = get<2>(e);
}

int search() {
	if (!possible(0, 0, 0))
		return -1;
	int base = 0;
	if (g[0][0] == 1)
		base++, g[0][0] = 0;
	if (g[n-1][n-1] == 1)
		base++, g[n-1][n-1] = 0;
	ret = 0;
	auto ch = SCC::remove_dead(0, 0);
//	printf("change %d\n", ch.size());
//	for (int i = 0; i < n; i++) {
//		for (int j = 0; j < n; j++) {
//			printf("%d ", g[i][j]);
//		}
//		puts("");
//	}
	limit_k = 1, test = 10000;
	ret = 0;
	dfs(0, 0, 0, 0, 0);
	int r1 = ret;
	ret = 0;
	limit_k = 2, test = 1000000;
	memcpy(g, ng, sizeof(ng));
	ret = 0;
	dfs(0, 0, 0, 0, 0);
	int r2 = ret;
	return r1 + r2 + base;
}

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		int x;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &x);
				g[i][j] = x;
			}
		}
		
		int ret = search();
		printf("%d\n", ret);
	}
	return 0;
}
/*
1
3
0 0 1
0 1 0
0 2 0

1
4
0 0 0 0
2 1 0 0
2 1 2 0
2 1 2 0

1
5
1 1 1 1 1
1 2 1 1 1
1 2 1 1 1
1 2 1 1 1
1 2 1 1 1

1
5
1 1 1 1 1
2 1 2 2 1
2 1 1 2 1
2 1 1 2 1
2 2 2 2 1

1
8
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
2 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 

1
6
1 1 1 1 1 1 
1 2 1 2 2 1 
1 1 1 1 2 1 
1 2 1 1 2 1 
1 2 2 2 2 1 
1 1 1 1 1 1 



2
11
1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 2 2
1 1 1 1 1 1 1 1 1 2 1

1
11
1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1
1 1 1 2 2 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 2 2 2 1 1 1
1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 2 2 1 1 1
1 1 1 1 1 1 2 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1

1
11
1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1
1 2 1 2 1 2 1 2 1 2 1
1 2 1 2 1 2 1 2 1 2 1
1 2 1 2 1 2 1 2 1 2 1
1 2 1 2 1 2 1 2 1 2 1
1 2 1 2 1 2 1 2 1 2 1
1 2 1 2 1 2 1 2 1 2 1
1 2 1 2 1 2 1 2 1 2 1
1 2 1 2 1 2 1 2 1 2 1
1 2 1 2 1 2 1 2 1 2 1
1
11
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0

1
11
1 1 0 1 2 2 2 1 0 0 2
0 1 1 1 1 2 2 0 0 0 1
1 0 1 0 0 2 1 1 1 1 2
0 1 2 1 1 2 0 2 0 2 0
2 0 2 0 0 0 0 2 0 1 0
2 2 1 0 2 0 1 1 2 0 0
2 1 2 2 0 0 2 0 2 1 1
1 2 0 2 0 1 0 1 0 2 2
2 0 1 0 0 2 1 1 0 1 1
1 2 2 1 1 1 2 1 1 1 1
2 0 2 1 1 2 1 2 1 2 0

1
11
2 0 0 1 0 1 1 2 1 2 2
0 2 0 1 2 0 1 0 2 2 1
2 2 0 0 2 2 2 0 1 2 0
1 2 2 0 1 0 1 0 2 0 1
1 0 2 0 1 1 0 2 2 0 1
1 0 0 0 2 2 0 1 0 0 2
0 0 1 0 2 1 2 0 1 1 1
2 2 1 1 0 1 2 2 1 0 0
2 2 0 2 1 1 1 1 2 0 0
2 2 2 1 1 0 2 0 0 2 0
1 2 2 1 0 2 2 2 2 0 0

1
11
0 1 2 2 2 0 0 1 1 1 1
0 1 1 1 2 2 2 0 1 1 2
2 0 2 2 2 2 1 1 1 0 0
0 0 1 0 1 1 1 1 2 2 2
1 2 1 0 0 1 1 0 2 0 0
0 1 2 1 2 2 1 0 0 0 2
0 0 2 1 1 0 1 2 0 0 0
2 1 1 2 0 0 0 2 2 1 1
2 0 2 2 1 2 0 0 1 1 1
2 2 0 2 0 2 0 2 0 0 0
2 2 1 2 0 2 1 0 0 0 0

1
11
1 1 0 0 1 0 2 0 1 2 2
0 0 2 1 1 0 0 0 0 2 2
1 1 1 2 0 0 0 2 1 0 1
1 0 0 2 2 2 0 1 0 2 0
1 0 1 2 1 0 0 2 0 0 1
0 0 2 2 1 0 1 1 0 0 1
0 0 0 0 1 0 1 2 0 1 2
1 0 0 0 0 1 1 0 1 0 1
0 2 1 2 0 2 2 0 1 2 0
0 0 0 2 1 0 2 0 0 1 1
2 2 2 2 2 0 0 0 2 1 0
*/

