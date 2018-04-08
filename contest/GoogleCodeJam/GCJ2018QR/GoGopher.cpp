#include <bits/stdc++.h>
using namespace std;
const int MAXN = 32;
int testcase;
int A, R, C;
int f[MAXN][MAXN];
int lx, ly, rx, ry;
struct Pos {
	int x, y, v;
	Pos(int x=0, int y=0, int v=0):
		x(x), y(y), v(v) {}
	bool operator<(const Pos &a) const {
		if (v != a.v)
			return v > a.v; 
		if (x != a.x)
			return x < a.x;
		return y < a.y;
	}
};
const int dx[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
const int dy[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
set<Pos> S;
set<Pos>::iterator Sit[MAXN][MAXN];
int adj(int x, int y) {
	int ret = 0;
	for (int i = 0; i < 9; i++) {
		int tx = x + dx[i], ty = y + dy[i];
		ret += f[tx][ty] == 0;
	}
	return ret;
}
int main() {
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &A);
		if (A == 20)
			R = 4, C = 5;
		else if (A == 200)
			R = 14, C = 15;
		else
			assert(false);
		lx = 1, ly = 1;
		rx = R, ry = C;
		memset(f, 0, sizeof(f));
		S.clear();
		for (int i = 0; i < MAXN; i++) {
			for (int j = 0; j < MAXN; j++)
				Sit[i][j] = S.end();
		}
		for (int i = lx+1; i <= rx-1; i++) {
			for (int j = ly+1; j <= ry-1; j++) {
				int a = adj(i, j);
				Sit[i][j] = S.insert(Pos(i, j, a)).first;
			}
		}

		while (!S.empty()) {
			Pos t = *S.begin();
			printf("%d %d\n", t.x, t.y);
			fflush(stdout);
			int x, y;
			scanf("%d %d", &x, &y);
			if (x == 0 && y == 0)
				break;
			if (x == -1 && y == -1)
				assert(false);
			if (f[x][y] == 1)
				continue;
			f[x][y] = 1;
			for (int i = 0; i < 9; i++) {
				int tx = x + dx[i];
				int ty = y + dy[i];
				if (tx >= lx && tx <= rx && ty >= ly && ty <= ry) {
					if (Sit[tx][ty] != S.end()) {
						Pos v = *Sit[tx][ty];
						S.erase(Sit[tx][ty]);
						v.v--;
						if (v.v > 0)
							Sit[tx][ty] = S.insert(v).first;
					}
				}
			}
		}
	}
	return 0;
}
/*
1
20
*/
