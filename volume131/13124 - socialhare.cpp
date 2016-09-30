#include <bits/stdc++.h>
using namespace std;

int R, C, W;
char g[105][105], w[105];
int test(char w[]) {
	int n = strlen(w);
	const int dx[] = {0, 1, 1, -1};
	const int dy[] = {1, 0, 1, 1};
	
	int stk[105][2];
	int used[128] = {};
	for (int i = 0; i < n; i++)
		used[w[i]]++;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			for (int k = 0; k < 4; k++) {
				if (k == 0 && C-j < n)
					continue;
				if (k == 1 && R-i < n)
					continue;
				if (k == 2 && min(C-j, R-i) < n)
					continue;
				if (k == 3 && min(C-j, i+1) < n)
					continue;
				int x = i, y = j, t = 0;
				int err = 0;
				while (x >= 0 && y >= 0 && x < R && y < C && t < n) {
					used[g[x][y]]--;
					err |= used[g[x][y]] < 0;
					stk[t][0] = x, stk[t][1] = y, t++;
					if (err)
						break;
					x += dx[k], y += dy[k];
				}
				for (int idx = 0; idx < t; idx++)
					used[g[stk[idx][0]][stk[idx][1]]]++;
				if (t == n && !err) {
					return 1;
				}
			}
		}
	}
	return 0;
}
int main() {
	while (scanf("%d %d %d", &R, &C, &W) == 3) {
		for (int i = 0; i < R; i++)
			scanf("%s", g[i]);
		
		int ret = 0;
		for (int i = 0; i < W; i++) {
			scanf("%s", w);
			ret += test(w);
		}
		printf("%d\n", ret);
	}
	return 0;
}

