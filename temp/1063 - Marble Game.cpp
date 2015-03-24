#include <stdio.h>
#include <queue>
#include <map>
#include <string.h>
#include <algorithm>
using namespace std;

int N, W;
struct state {
	vector< pair<int, int> > xy;
	bool operator<(const state &a) const {
		for (int i = 0; i < xy.size(); i++)
			if (xy[i] != a.xy[i])
				return xy[i] < a.xy[i];
		return false;
	}
	int isComplete() {
		int ok = 1;
		for (int i = 0; i < xy.size() && ok; i++)
			ok &= xy[i].first < 0;
		return ok;
	} 
};
int g[4][4][4];
pair<int, int> goal[64];
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int isValid(int x, int y) {
	return x >= 0 && y >= 0 && x < W && y < W;
}

state eraseGoal(state u) {
	for (int i = 0; i < u.xy.size(); i++) {
		if (u.xy[i] == goal[i])
			u.xy[i] = pair<int, int>(-1, -1);
	}
	return u;
}
state rotateMap(state u, int dir, int& ok) {
	ok = 1;
	int update = 1, tx, ty, x, y;
	int used[4][4] = {}, usedg[4][4] = {};
	for (int i = 0; i < u.xy.size(); i++) {
		x = u.xy[i].first, y = u.xy[i].second;
		if (x == -1)	continue;
		used[x][y] = 1;
		x = goal[i].first, y = goal[i].second;
		usedg[x][y] = i+1;
	}
	do {
		update = 0;
		for (int i = 0; i < u.xy.size(); i++) {
			while (u.xy[i].first >= 0) {
				x = u.xy[i].first, y = u.xy[i].second;
				tx = x + dx[dir], ty = y + dy[dir];
				if (isValid(tx, ty) && !g[x][y][dir] && usedg[tx][ty] && usedg[tx][ty] != i+1)
					ok = 0;
				if (isValid(tx, ty) && !g[x][y][dir] && (!used[tx][ty] || goal[i] == make_pair(tx, ty))) {
					used[x][y] = 0, used[tx][ty] = 1;
					u.xy[i] = pair<int, int>(tx, ty);
					update = 1;
					if (goal[i] == pair<int, int>(tx, ty)) {
						u.xy[i] = pair<int, int>(-1, -1);
						used[tx][ty] = 0, usedg[tx][ty] = 0;
					}
				} else {
					break;
				}
			}
		} 
	} while (update);
	return u;
}
void print(state u) {
	int used[4][4] = {}, x, y;
	for (int i = 0; i < u.xy.size(); i++) {
		x = u.xy[i].first, y = u.xy[i].second;
		if (x == -1)
			continue;
		used[x][y] = i+1;
	}
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < W; j++)
			printf("%d ", used[i][j]);
		puts("");
	}
	puts("--");
}
int bfs(state init) {
	state u, v;
	queue<state> Q;
	map<state, int> R;
	int f;
	
	init = eraseGoal(init);
	Q.push(init), R[init] = 0;
//	print(init);
	if (init.isComplete())
		return 0;
	
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		int step = R[u];
		
//		print(u);
//		printf("step %d\n", step);
		for (int i = 0; i < 4; i++) {
			v = rotateMap(u, i, f);
			v = eraseGoal(v);
			if (!f || R.count(v))		continue;
			if (v.isComplete())
				return step + 1;
			R[v] = step + 1;
//			print(v);
			Q.push(v);
		}
//		puts("--------------");
//		getchar();
	}
	return -1;
}
int main() {
	int x, y, tx, ty, M;
	int sx, sy, ex, ey;
	int cases = 0;
	while (scanf("%d %d %d", &W, &N, &M) == 3 && N+W+M) {
		state init;
		memset(g, 0, sizeof(g));
		
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &x, &y);
			init.xy.push_back(pair<int, int>(x, y));
		}
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &x, &y);
			goal[i] = pair<int, int>(x, y);
		}
		for (int i = 0; i < M; i++) {
			scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
			for (int j = 0; j < 4; j++) {
				tx = sx + dx[j], ty = sy + dy[j];
				if (tx == ex && ty == ey)
					g[sx][sy][j] = 1;
				tx = ex + dx[j], ty = ey + dy[j];
				if (tx == sx && ty == sy)
					g[ex][ey][j] = 1;
			}
		}
		
		int step = bfs(init);
		
		printf("Case %d: ", ++cases);
		if (step < 0)
			puts("impossible");
		else
			printf("%d moves\n", step);
		puts("");
	}
	return 0;
}
/*
3 1 5
1 2
1 0
2 1 2 2
0 0 1 0
0 1 1 1
0 2 1 2
1 1 2 1

4 3 1
0 1 
1 0 
1 2 
2 3 
2 1 
3 2 
1 1 1 2

3 2 2
0 0 
0 1 
0 2 
2 0 
2 0 1 0
2 0 2 1
*/
