#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int check(int qx[], int qy[], int n) {
	static int used[32] = {}, testcase = 0;
	testcase++;
	for (int i = 0; i < n; i++) {
		if (used[qx[i]] == testcase) return 0;
		used[qx[i]] = testcase;
	}
	testcase++;
	for (int i = 0; i < n; i++) {
		if (used[qy[i]] == testcase) return 0;
		used[qy[i]] = testcase;
	}
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			if (abs(qx[i] - qx[j]) == abs(qy[i] - qy[j]))
				return 0;
		}
	}
	return 1;
}
int main() {
	int n, cases = 0, tx, ty;
	char g[32][32];
	const int dx[] = {0, 0, 1, 1, 1, -1, -1, -1};
	const int dy[] = {1, -1, 0, 1, -1, 0, 1, -1};
	while (scanf("%d", &n) == 1) {
		if (cases++)	puts("");
		for (int i = 0; i < n; i++)
			scanf("%s", g[i]);
		int qx[32], qy[32], m = 0;
		for (int i = 0; i < n;i++) {
			for (int j = 0; j < n; j++) {
				if (g[i][j] == 'X')
					qx[m] = i, qy[m] = j, m++;
			}
		}
		if (check(qx, qy, m))
			puts("YES");
		else {
			puts("NO");
			int ok = 0;
			for (int i = 0; i < m && !ok; i++) {
				for (int j = 0; j < 8 && !ok; j++) {
					tx = qx[i] + dx[j], ty = qy[i] + dy[j];
					while (true) {
						if (tx < 0 || ty < 0 || tx >= n || ty >= n)
							break;
						if (g[tx][ty] == '0') {
							swap(tx, qx[i]), swap(ty, qy[i]);
							if (check(qx, qy, m)) {
								puts("YES");
								ok = 1;
								swap(g[qx[i]][qy[i]], g[tx][ty]);
								for (int i = 0; i < n; i++)
									puts(g[i]);
								break;
							}
							swap(tx, qx[i]), swap(ty, qy[i]);
						}
						tx += dx[j], ty += dy[j];
					}
				}
			}
			if (!ok)
				puts("NO");
		}
	}
	return 0;
}
/*
5
00X00
X0000
000X0
0X000
0000X
5
0X000
X0000
000X0
0X000
0000X
*/
