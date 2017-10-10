#include <bits/stdc++.h> 
using namespace std;

int main() {
	const int dx[] = {1, 0, -1, 0};
	const int dy[] = {0, -1, 0, 1};
	int testcase, n, m;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		const int MAXN = 60;
		int g[MAXN][MAXN] = {}, sx, sy;
		for (int i = 0; i < m; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			g[x][y] = 1;
		}
		
		scanf("%d %d", &sx, &sy);
		int dir;
		if (sx == 0)
			dir = 0;
		else if (sx == n+1)
			dir = 2;
		else if (sy == 0)
			dir = 3;
		else
			dir = 1;
			
		do {
			sx += dx[dir], sy += dy[dir];
			if (g[sx][sy])
				dir = (dir+1)%4;
		} while (sx >= 1 && sy >= 1 && sx <= n && sy <= n);
		printf("%d %d\n", sx, sy);
	}
	return 0;
}
/*
2
2 3
1 1
1 2
2 2
3 1

3 6
1 1
1 3
2 2
2 3
3 1
3 2
2 0
*/
