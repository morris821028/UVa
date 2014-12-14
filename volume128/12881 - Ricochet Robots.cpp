#include <stdio.h>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

int N, W, H, L;
struct state {
	pair<int, int> xy[4];
	bool operator<(const state &a) const {
		for (int i = 0; i < N; i++)
			if (xy[i] != a.xy[i])
				return xy[i] < a.xy[i];
		return false;
	}
	void normal() {
		sort(xy + 1, xy + N);
	}
};
char g[16][16];
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int isValid(int x, int y) {
	return x >= 0 && y >= 0 && x < H && y < W;
}
int bfs(state init, int L) {
	state u, v;
	queue<state> Q;
	map<state, int> R;
	int x, y, tx, ty;
	int used[11][11] = {}, testcase = 0;
	init.normal();
	Q.push(init), R[init] = 0;
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		int step = R[u];
		if (g[u.xy[0].first][u.xy[0].second] == 'X')
			return step;
		if (step > L)
			continue;
		testcase++;
		for (int i = 0; i < N; i++) {
			x = u.xy[i].first, y = u.xy[i].second;
			used[x][y] = testcase;
		}
		for (int i = 0; i < N; i++) {
			x = u.xy[i].first, y = u.xy[i].second;
			for (int j = 0; j < 4; j++) {
				tx = x, ty = y;
				while (isValid(tx + dx[j], ty + dy[j])) {
					if (g[tx + dx[j]][ty + dy[j]] == 'W')
						break;
					if (used[tx + dx[j]][ty + dy[j]] == testcase)
						break;
					tx += dx[j], ty += dy[j];					
				}
				v = u, v.xy[i] = make_pair(tx, ty);
				v.normal();
				if (R.find(v) == R.end()) {
					R[v] = step + 1;
					Q.push(v);
				}
			}
		}
	}
	return 0x3f3f3f3f;
}
int main() {
	while (scanf("%d %d %d %d", &N, &W, &H, &L) == 4) {
		for (int i = 0; i < H; i++)
			scanf("%s", g[i]);
		
		state init;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				if (g[i][j] >= '1' && g[i][j] <= '9')
					init.xy[g[i][j] - '1'] = make_pair(i, j);
			}
		}
		
		int ret = bfs(init, L);
		if (ret > L)
			puts("NO SOLUTION");
		else
			printf("%d\n", ret);
	}
	return 0;
}
/*
2 5 4 10
.2...
...W.
WWW..
.X.1.
1 5 4 10
.....
...W.
WWW..
.X.1.
*/
