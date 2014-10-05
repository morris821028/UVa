#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;

int parent[1048576], weight[1048576];
int used[1024][1024];
const int dx[] = {1, 1, 1, -1, -1, -1, 0, 0};
const int dy[] = {0, 1, -1, 0, 1, -1, 1, -1};
int findp(int x) {
	return parent[x] == x ? parent[x] : parent[x] = findp(parent[x]);
}
int joint(int p, int q) {
	p = findp(p), q = findp(q);
	if (weight[p] > weight[q])
		weight[p] += weight[q], parent[q] = p;
	else
		weight[q] += weight[p], parent[p] = q;
	return 1;
}
int main() {
	int n, m, Q, cases = 0;
	int x, y, tx, ty;
	while (scanf("%d %d %d", &n, &m, &Q) == 3) {
		cases++;
		int N = n * m + 10, up = n * m + 1, down = n * m + 2;
		int p, q, A[8];
		for (int i = 0; i < N; i++)
			parent[i] = i, weight[i] = 1;
		for (int i = 0; i < Q; i++) {
			scanf("%d %d", &x, &y);
			p = x * m + y;
			up = findp(up), down = findp(down);
			int s = 0;
			for (int j = 0; j < 8; j++)	{
				tx = x + dx[j], ty = y + dy[j];
				if (ty < 0 || ty >= m)	{
					A[j] = p;
					continue;
				}
				if (tx < 0)			q = up;
				else if(tx >= n)	q = down;
				else {
					if (used[tx][ty] != cases) {
						A[j] = p;
						continue;
					}
					q = tx * m + ty;
				}
				if (findp(q) == up)		s |= 1;
				if (findp(q) == down)	s |= 2;
				A[j] = q;
			}
			if (s != 3) {
				puts("<(_ _)>");
				for (int j = 0; j < 8; j++) {
					joint(p, A[j]);
				}
				used[x][y] = cases;
			} else {
				puts(">_<");
			}
		}
	}
	return 0;
}
