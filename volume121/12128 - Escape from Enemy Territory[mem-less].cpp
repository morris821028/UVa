#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <bitset>
using namespace std;

static const int MAXN = 1005;
static const int dx[] = {0, 0, -1, 1};
static const int dy[] = {-1, 1, 0, 0};
int n, X, Y, sx, sy, ex, ey;
vector< std::pair<int, int> > A;
#define GET(x) (g[x>>5]>>(x&31)&1)
#define SET(x) (g[x>>5] |= 1<<(x&31))
int64_t g[((MAXN*MAXN)>>5)+1];
struct DisjointSet {
	int parent[MAXN*MAXN];
	void init(int n) {
		for (int i = 0; i < n; i++)
			parent[i] = i;
	}
	int findp(int x) {
		return parent[x] == x ? x : parent[x] = findp(parent[x]);
	}
	int joint(int x, int y) {
		x = findp(x), y = findp(y);
		parent[x] = y;
	}
} DS;
int flood() {
	const int st = sx*Y+sy, ed = ex*Y+ey;
	sort(A.begin(), A.end());
	vector<int> q, q2, B;
	vector<int> C;
	memset(g, 0, sizeof(g[0])*(((X*Y)>>5)+1));
	B.reserve(X*Y);
	for (int i = 0; i < A.size(); i++) {
		pair<int, int> &e = A[i];
		SET(e.first*Y+e.second);
		q.push_back(e.first*Y+e.second);
	}
	C.push_back(0);
	for (; !q.empty(); ) {
		while (!q.empty()) {
			int u = q.back(); q.pop_back();
			int x = u/Y, y = u%Y;
			B.push_back(u);
			for (int i = 0; i < 4; i++) {
				int tx = x + dx[i], ty = y + dy[i];
				if (tx < 0 || ty < 0 || tx >= X || ty >= Y)
					continue;
				int v = tx*Y+ty;
				if (GET(v) == 0) {
					SET(v);
					q2.push_back(v);
				}
			}
		}
		C.push_back(B.size());
		q.swap(q2);
	}
	
	DS.init(X*Y);
	memset(g, 0, sizeof(g[0])*(((X*Y)>>5)+1));
	for (int i = C.size()-1; i >= 1; i--) {
		int r = C[i], l = C[i-1];
		int flag = 0;
		for (int j = r-1; j >= l; j--) {
			int u = B[j];
			SET(u);
			int x = u/Y, y = u%Y;
			for (int k = 0; k < 4; k++) {
				int tx = x + dx[k], ty = y + dy[k];
				if (tx < 0 || ty < 0 || tx >= X || ty >= Y)
					continue;
				int v = tx*Y+ty;
				if (GET(v))
					DS.joint(u, v);
			}
		}
		if (DS.findp(st) == DS.findp(ed))
			return i-1;
	}
	return 0;
}
pair<int, int> bfs() {
	if (sx == ex && sy == ey)
		return {0, 0};
	int st = sx*Y+sy, ed = ex*Y+ey;
	if (st > ed)	swap(st, ed);
	int depth = flood(), step = 0;
	static bitset<MAXN*MAXN> visited; visited.reset();
	vector<int> q, q2;
	q.push_back(st);
	visited.set(st);
	for (; !q.empty();) {
		while (!q.empty()) {
			int u = q.back(); q.pop_back();
			if (u == ed)
				return {depth, step};
			int x = u/Y, y = u%Y;
			for (int i = 0; i < 4; i++) {
				int tx = x + dx[i], ty = y + dy[i];
				if (tx < 0 || ty < 0 || tx >= X || ty >= Y)
					continue;
				int v = tx*Y+ty;
				if (GET(v) && visited[v] == 0) {
					visited.set(v);
					q2.push_back(v);
				}
			}
		}
		q.swap(q2), step++;
	}
	return {depth, -1};
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d", &n, &X, &Y);
		scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
		A.clear();
		for (int i = 0; i < n; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			A.push_back({x, y});
		}
		pair<int, int> ret = bfs();
		printf("%d %d\n", ret.first, ret.second);
	}
	return 0;
}
/*
2
1 2 2
0 0 1 1
0 1
2 5 6
0 0 4 0
2 1
2 3

1
12 7 5
0 0 6 4
0 1
1 1
2 1
3 1
4 1
5 1
1 3
2 3
3 3
4 3
5 3
6 3
*/
