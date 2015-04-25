#include <stdio.h> 
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 64;
int A[MAXN][MAXN];
vector< pair<int, int> > g[128];

int parent[MAXN*MAXN], weight[MAXN*MAXN];

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
void init(int n)  {
	for (int i = 0; i <= n; i++)
		parent[i] = i, weight[i] = 1;
}

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
int query(int n, int m, int need) {
	int x, y, tx, ty;
	int ret = 0x3f3f3f3f;
	for (int i = 0; i < 100; i++) { // lower
		init(n * m);
		
		int ok = 0;
		for (int j = i; j < 100 && !ok; j++) { // upper
			if (j - i >= ret)
				break;
			for (int k = 0; k < g[j].size() && !ok; k++) {
				x = g[j][k].first, y = g[j][k].second;
				for (int d = 0; d < 4; d++) {
					tx = x + dx[d], ty = y + dy[d];
					if (tx < 0 || ty < 0 || tx >= n || ty >= m)
						continue;
					if (A[tx][ty] <= j && A[tx][ty] >= i) {
						joint(x * m + y, tx * m + ty);
						if (weight[findp(x * m + y)] >= need)
							ok = 1, ret = min(ret, j - i);
					}
				}
			}
		}
		
	}
	return ret;
}
int main() {
	int n, m, q, x;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < 100; i++)
			g[i].clear();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				scanf("%d", &A[i][j]);
				g[A[i][j]].push_back(make_pair(i, j));
			}
		}
		scanf("%d", &q);
		for (int i = 0; i < q; i++) {
			scanf("%d", &x);
			printf("%d\n", query(n, m, x));
		}
	}
	return 0;
}
/*
5 10
0 0 3 46 0 46 0 0 12 12
0 0 13 50 49 46 11 10 10 11
0 51 51 49 99 99 89 0 0 10
0 0 48 82 70 99 0 52 13 14
51 50 50 51 70 35 70 10 14 11
6
1
5
10
12
47
50
*/
