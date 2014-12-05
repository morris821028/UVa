#include <stdio.h>
#include <algorithm>
using namespace std;

int g[32][32], n, m;
int A[900][2], N, SUM = 0;
int isEmpty() {
	return SUM == 0;
}
void remove(int x, int y, int w) {
	for (int i = x - w; i <= x + w; i++)
		g[i][y]--, SUM--;
	for (int i = y - w; i <= y + w; i++)
		g[x][i]--, SUM--;
	g[x][y]++, SUM++;
}
void resume(int x, int y, int w) {
	for (int i = x - w; i <= x + w; i++)
		g[i][y]++, SUM++;
	for (int i = y - w; i <= y + w; i++)
		g[x][i]++, SUM++;
	g[x][y]--, SUM--;
}
int place(int x, int y, int w) {
	for (int i = x - w; i <= x + w; i++)
		if (!g[i][y])
			return 0;
	for (int i = y - w; i <= y + w; i++)
		if (!g[x][i])
			return 0;
	return 1;
}
int dfs(int idx, int used, int LX, int LY) {
	if (isEmpty()) {
		printf("%d\n%d %d\n", used, LX + 1, LY + 1);
		return 1;
	}
	if (idx == N)
		return 0;
	int t = min(min(A[idx][0], A[idx][1]), min(n - 1 - A[idx][0], m - 1 - A[idx][1]));
	for (int i = t; i >= 1; i--) {
		if (place(A[idx][0], A[idx][1], i)) {
			remove(A[idx][0], A[idx][1], i);
			if (dfs(idx+1, used + 1, A[idx][0], A[idx][1]))
				return 1;
			resume(A[idx][0], A[idx][1], i);
		}
	}
	if (dfs(idx+1, used, LX, LY))
		return 1;
	return 0;
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &g[i][j]), SUM += g[i][j];
		N = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (g[i][j] == 1)
					A[N][0] = i, A[N][1] = j, N++;
		dfs(0, 0, -1, -1);
	}
	return 0;
}
/*
2
5 5
0 1 1 0 0
1 1 2 0 0
1 2 1 1 1
0 0 1 0 0
0 0 1 0 0
10 11
0 0 0 0 1 1 0 0 0 0 0
0 0 0 0 1 1 0 1 0 0 0
0 0 1 1 1 2 2 1 1 0 0
0 0 1 2 2 1 1 2 2 0 0
0 0 1 1 3 1 0 0 1 0 0
0 0 0 2 1 2 2 1 1 1 1
0 1 0 0 1 1 1 0 1 1 0
1 1 1 0 1 1 1 1 3 1 1
0 1 0 0 0 0 1 0 0 1 0
0 0 0 0 0 0 1 0 0 0 0
*/

