#include <bits/stdc++.h>
using namespace std;

char g[8][8];
int R[8][8], C[8][8], G[8][8];
int XY[32][32], val[32], n;
int dfs(int idx) {
	if (idx == n) {
		for (int i = 0; i < n; i++)
			g[XY[i][0]][XY[i][1]] = val[i] + '0';
		for (int i = 0; i < 4; i++)
			puts(g[i]);
		return 1;
	}
	int i = XY[idx][0], j = XY[idx][1];
	for (int c = 1; c <= 4; c++) {
		if (R[i][c] || C[j][c])
			continue;
		int gid = (i/2)*2 + j/2;
		if (G[gid][c])
			continue;
		val[idx] = c;
		R[i][c] = C[j][c] = G[gid][c] = 1;
		if (dfs(idx+1))
			return 1;
		R[i][c] = C[j][c] = G[gid][c] = 0;
	}
}
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		for (int i = 0; i < 4; i++)
			scanf("%s", g[i]);
			
		memset(R, 0, sizeof(R));
		memset(C, 0, sizeof(C));
		memset(G, 0, sizeof(G));
		
		n = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (g[i][j] != '*') {
					int c = g[i][j] - '0';
					R[i][c] = C[j][c] = G[(i/2)*2 + j/2][c] = 1;
				} else {
					XY[n][0] = i, XY[n][1] = j, n++;
				}
			}
		}
		printf("Case #%d:\n", ++cases);
		dfs(0);
	}
	return 0;
}

