#include <bits/stdc++.h>
using namespace std;

const int MAXN = 64;
const int MAXP = 5040;	// lcm(2, 4, 6, 8, ..., 18)
const int dx[] = {0, 0, -1, 1, 0};
const int dy[] = {-1, 1, 0, 0, 0};
char g[MAXN][MAXN], p[MAXN][MAXN];

struct Stat {
	int x, y, t;
	Stat(int x=0, int y=0, int t=0):
		x(x), y(y), t(t) {}
	bool operator<(const Stat &s) const {
		if (t != s.t)
			return t < s.t;
		if (x != s.x)
			return x > s.x;
		return y > s.y;
	}
};

bitset<MAXP> used[MAXN][MAXN];
int main() {
	int cases = 0;
	int n;
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++)
			scanf("%s", g[i]);
		for (int i = 0; i < n; i++)
			scanf("%s", p[i]);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				used[i][j].reset();
		}

		queue<Stat> S;
		S.push(Stat(0, 0, 0));
		used[0][0][0] = 1;
		int ret = -1;
		while (!S.empty()) {
			Stat u = S.front(); S.pop();
			if (u.x == n-1 && u.y == n-1) {
				ret = u.t;
				break;
			}
			for (int i = 0; i < 5; i++) {
				int tx = u.x + dx[i];
				int ty = u.y + dy[i];
				if (tx < 0 || ty < 0 || tx >= n || ty >= n || g[tx][ty] == '*')
					continue;
				int tt = u.t+1, pp = p[tx][ty]-'0';
				if (pp) {
					int mm = tt%(2*pp);
					if (mm >= pp || used[tx][ty][tt%MAXP])
						continue;
					used[tx][ty][tt%MAXP] = 1;
					S.push(Stat(tx, ty, tt));
				} else {
					pp = MAXP;
					int mm = tt%pp;
					if (used[tx][ty][mm])
						continue;
					used[tx][ty][mm] = 1;
					S.push(Stat(tx, ty, tt));
				}
			}
		}
		
		if (cases++)
			puts("");
		if (ret == -1)
			puts("NO");
		else
			printf("%d\n", ret);
	}
	return 0;
}
/*
10
.*********
........**
*.******.*
*.******.*
*.******.*
*........*
*.******.*
*.******.*
*........*
********..
0000000000
0000000000
0000000000
0000000000
0000000000
0123456780
0000000000
0000000000
0123456780
0000000000

3
...
**.
**.
021
002
000
*/ 
