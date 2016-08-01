#include <bits/stdc++.h>
using namespace std;

char g[64][64], s[32767];
int to_where[64][64][4][2];
int R, C;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

inline int isValid(int x, int y) {
	return x >= 0 && y >= 0 && x < R && y < C;
}
struct Node {
	int x, y, d;
	Node(int x, int y, int d):x(x), y(y), d(d) {
	}
	bool operator<(const Node &a) const {
		if (d != a.d)
			return d < a.d;
		if (x != a.x)
			return x < a.x;
		return y < a.y;
	}
};

int main() {
	while (scanf("%d %d", &R, &C) == 2) {
		for (int i = 0; i < R; i++)
			scanf("%s", g[i]);
		scanf("%s", s);
		
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				for (int k = 0; k < 4; k++) {
					int x = i, y = j;
					int tx = x, ty = y;
					to_where[i][j][k][0] = -1;
					to_where[i][j][k][1] = -1;
					while (isValid(tx+dx[k], ty+dy[k]) && g[tx][ty] == g[x][y])
						tx += dx[k], ty += dy[k];
					if (g[tx][ty] == g[x][y])
						continue;
					to_where[i][j][k][0] = tx;
					to_where[i][j][k][1] = ty;
				}
			}
		}
		
		int n = strlen(s);
		s[n] = '*', s[n+1] = '\0';
		n++;
		
		queue<Node> pQ;
		int dist[64][64] = {}, inq[64][64] = {};
		memset(dist, 0x3f, sizeof(dist));
		dist[0][0] = 0;
		pQ.push(Node(0, 0, 0));
		for (int i = 0; i < n; i++) {
			Node u(0, 0, 0);
			while (!pQ.empty()) {
				u = pQ.front(), pQ.pop();
				inq[u.x][u.y] = 0;
				int d = dist[u.x][u.y];
				for (int k = 0; k < 4; k++) {
					if (to_where[u.x][u.y][k][0] == -1)
						continue;
					int x = to_where[u.x][u.y][k][0];
					int y = to_where[u.x][u.y][k][1];
					if (dist[x][y] > d+1) {
						dist[x][y] = d+1;
						if (inq[x][y] == 0) {
							pQ.push(Node(x, y, d+1));
							inq[x][y] = 1;
						}
					}
				}
			}
			for (int j = 0; j < R; j++) {
				for (int k = 0; k < C; k++) {
					if (g[j][k] == s[i]) {
						dist[j][k] = dist[j][k]+1;
						pQ.push(Node(j, k, dist[j][k])), inq[j][k] = 1;
					} else {
						dist[j][k] = 0x3f3f3f3f;
					}
				}
			}
		}
		
		int ret = 0x3f3f3f3f;
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if (g[i][j] == '*')
					ret = min(ret, dist[i][j]);
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}

