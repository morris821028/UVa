#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <set>
using namespace std;
#define MAXN 512
int V[MAXN][MAXN], R[MAXN][MAXN], C[MAXN][MAXN];
int dist[MAXN][MAXN];
set<int> next_update[MAXN];
struct Node {
	int r, c, v, h;
	Node(int a=0, int b=0, int d=0, int e=0):
		r(a), c(b), v(d), h(e) {}
	bool operator<(const Node &x) const {
		if (v != x.v)
			return v > x.v;
		return h > x.h;
	}
};
int findPath(int n, int m, int sx, int sy, int ex, int ey) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			dist[i][j] = 0x3f3f3f3f;
			next_update[i].insert(j);
		}
	}
	dist[sx][sy] = 0;
	priority_queue<Node> pQ;
	Node u;
	int lr, rr, lc, rc, d;
	pQ.push(Node(sx, sy, 0, abs(sx-ex) + abs(sy-ey)));
	while (!pQ.empty()) {
		u = pQ.top(), pQ.pop();
		if (dist[u.r][u.c] + V[u.r][u.c] < u.v)
			continue;
		next_update[u.r].erase(u.c);
//		printf("%d %d %d ---\n", u.r, u.c, u.v);
		if (u.r == ex && u.c == ey)
			return dist[ex][ey];
		d = dist[u.r][u.c] + V[u.r][u.c];
		if (d >= dist[ex][ey])
			continue;
		lr = max(0, u.r - R[u.r][u.c]);
		rr = min(n-1, u.r + R[u.r][u.c]);
		lc = max(0, u.c - C[u.r][u.c]);
		rc = min(m-1, u.c + C[u.r][u.c]);
		for (int k = 0; k < 30; k++) {
			int i = rand()%(rr - lr + 1) + lr;
			int j = rand()%(rc - lc + 1) + lc;
			if (dist[i][j] > d) {
				dist[i][j] = d;
				pQ.push(Node(i, j, d + V[i][j], abs(i-ex) + abs(j-ey)));
			}
		}
#define CUT 1
//		for (int i = lr; i <= rr; i++) {
////			if (lr + CUT <= i && i <= rr - CUT)
////				continue;
//			set<int>::iterator it = lower_bound(next_update[i].begin(), next_update[i].end(), lc);
//			for (; it != next_update[i].end() && *it <= rc; it++) {
//				int j = *it;
////				if (lc + CUT <= j && j <= rc - CUT)
////					continue;
//				if (dist[i][j] > d) {
//					dist[i][j] = d;
//					pQ.push(Node(i, j, d + V[i][j], abs(i-ex) + abs(j-ey)));
//				}
//			}
//		}
		if (u.r == sx && u.c == sy) {
			for (int i = lr; i <= rr; i++) {
				set<int>::iterator it = lower_bound(next_update[i].begin(), next_update[i].end(), lc);
				for (; it != next_update[i].end() && *it <= rc;) {
					int j = *it;
					next_update[i].erase(it++);
				}
			}
		}
	}
	return -1;
}
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	int n, m, q, X[16], Y[16];
	while (scanf("%d %d %d", &n, &m, &q) == 3) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &V[i][j]);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &R[i][j]);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &C[i][j]);
		for (int i = 0; i < q; i++) {
			scanf("%d %d", &X[i], &Y[i]);
			X[i]--, Y[i]--;
		}
		for (int i = 1; i < q; i++) {
			int r = findPath(n, m, X[i-1], Y[i-1], X[i], Y[i]);
			printf("%d%c", r, i == q - 1 ? '\n' : ' ');
		}
	}
	return 0;
}
/*
3 4 5
1 2 1 1
1 5 3 4
1 1 6 3
1 2 3 3
3 3 1 2
0 0 0 1
1 4 0 1
2 3 0 1
4 1 3 1
1 1
3 4
1 1
2 2
2 2
*/
