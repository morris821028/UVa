#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm> 
using namespace std;

#define MAXN 1024
int g[MAXN][MAXN], h[131072], out[131072];
int parent[MAXN * MAXN], weight[MAXN * MAXN];

struct Pos {
	int x, y, h;
	Pos(int a = 0, int b = 0, int c = 0):
		x(a), y(b), h(c) {}
	bool operator<(const Pos &a) const {
		return h > a.h;
	}
};

int findp(int x) {
	return parent[x] == x ? x : parent[x] = findp(parent[x]);
}
int joint(int x, int y) {
	x = findp(x), y = findp(y);
	if (x == y)	return 0;
	if (weight[x] > weight[y])
		weight[x] += weight[y], parent[y] = x;
	else
		weight[y] += weight[x], parent[x] = y;
	return 1;
}
int main() {
	const int dx[] = {0, 0, 1, -1};
	const int dy[] = {1, -1, 0, 0};
	int testcase, n, m, q, tx, ty;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &g[i][j]);
		scanf("%d", &q);
		for (int i = 0; i < q; i++)
			scanf("%d", &h[i]);
			
		vector<Pos> D;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				D.push_back(Pos(i, j, g[i][j]));
			}
		}
		sort(D.begin(), D.end());
		int idx = 0, nm = n*m, sum = 0;
		Pos u;
		for (int i = nm; i >= 0; i--)
			parent[i] = i, weight[i] = 1;
		for (int i = q - 1; i >= 0; i--) {
			while (idx < nm && D[idx].h > h[i]) {
				sum++;
				u = D[idx++];
//				printf("add %d %d - %d\n", u.x, u.y, u.h);
				for (int j = 0; j < 4; j++) {
					tx = u.x + dx[j], ty = u.y + dy[j];
					if (tx < 0 || ty < 0 || tx >= n || ty >= m)
						continue;
					if (g[tx][ty] > h[i]) {
						sum -= joint(u.x * m + u.y, tx * m + ty);
					}
				}
			}
			out[i] = sum;
//			printf("%d\n", sum);
		}
		for (int i = 0; i < q; i++)
			printf("%d ", out[i]);
		puts("");
	}
	return 0;
}
