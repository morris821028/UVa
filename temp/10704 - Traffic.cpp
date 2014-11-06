#include <stdio.h> 
#include <string.h>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;
#define hash_mod 1000003
struct state {
	char g[6][6];
	unsigned int hash() {
		unsigned int a = 63689, b = 378551;
		unsigned int value = 0;
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				value = value * a + g[i][j];
				a *= b;
			}
		}
		return value % hash_mod;
	}
	bool operator<(const state &a) const {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				if (g[i][j] != a.g[i][j])
					return g[i][j] < a.g[i][j];
			}
		}
		return false;
	}
	void print() {
		for (int i = 0; i < 6; i++, puts(""))
			for (int j = 0; j < 6; j++)
				printf("%c", g[i][j]);
		puts("--");
	}
};
void color(state &s, int x, int y, int w, int h, char c) {
	for (int i = x; i < x + w; i++)
		for (int j = y; j < y + h; j++)
			s.g[i][j] = c;
}
map<state, int> hash[hash_mod];
state shiftup(state &u, int x, int y) {
	state v = u;
	char c = v.g[x][y];
	for (int i = 0; x+i < 6 && v.g[x+i][y] == c; i++)
		swap(v.g[x+i-1][y], v.g[x+i][y]);
	return v;
}
state shiftdown(state &u, int x, int y) {
	state v = u;
	char c = v.g[x][y];
	for (int i = 0; x+i >= 0 && v.g[x+i][y] == c; i--)
		swap(v.g[x+i+1][y], v.g[x+i][y]);
	return v;
}
state shiftleft(state &u, int x, int y) {
	state v = u;
	char c = v.g[x][y];
	for (int i = 0; y+i < 6 && v.g[x][y+i] == c; i++)
		swap(v.g[x][y+i-1], v.g[x][y+i]);
	return v;
}
state shiftright(state &u, int x, int y) {
	state v = u;
	char c = v.g[x][y];
	for (int i = 0; y+i >= 0 && v.g[x][y+i] == c; i--)
		swap(v.g[x][y+i+1], v.g[x][y+i]);
	return v;
}
int bfs(state init) {
	for (int i = 0; i < hash_mod; i++)
		hash[i].clear();
	int h = init.hash(), ti, tj;
	state u, v;
	queue<state> Q;
	Q.push(init), hash[h][init] = 0;
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		h = u.hash();
		int step = hash[h][u];
		if (u.g[2][4] == 'w' && u.g[2][5] == 'w') {
//			u.print();
			return step;
		}
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				if (u.g[i][j] < 'a' || u.g[i][j] > 'z')
					continue;
				ti = i, tj = j;
				v = u;
				while (ti-1 >= 0 && v.g[ti-1][tj] == ' ' && ti+1 < 6 && v.g[ti][tj] == v.g[ti+1][tj]) { // shift up
					v = shiftup(v, ti, tj);
					ti--;
					h = v.hash();
					if (hash[h].find(v) == hash[h].end()) {
						hash[h][v] = step+1;
						Q.push(v);
					}
//					v.print();
				}
				ti = i, tj = j;
				v = u;
				while (ti-1 >= 0 && v.g[ti-1][tj] == v.g[ti][tj] && ti+1 < 6 && v.g[ti+1][tj] == ' ') { // shift down
					v = shiftdown(v, ti, tj);
					ti++;
					h = v.hash();
					if (hash[h].find(v) == hash[h].end()) {
						hash[h][v] = step+1;
						Q.push(v);
					}
//					v.print();
				}
				ti = i, tj = j;
				v = u;
				while (tj-1 >= 0 && v.g[ti][tj-1] == ' ' && tj+1 < 6 && v.g[ti][tj] == v.g[ti][tj+1]) { // shift left
					v = shiftleft(v, ti, tj);
					tj--;
					h = v.hash();
					if (hash[h].find(v) == hash[h].end()) {
						hash[h][v] = step+1;
						Q.push(v);
					}
//					v.print();
				}
				ti = i, tj = j;
				v = u;
				while (tj-1 >= 0 && v.g[ti][tj-1] == v.g[ti][tj] && tj+1 < 6 && v.g[ti][tj+1] == ' ') { // shift right
					v = shiftright(v, ti, tj);
					tj++;
					h = v.hash();
					if (hash[h].find(v) == hash[h].end()) {
						hash[h][v] = step+1;
						Q.push(v);
					}
//					v.print();
				}
			}
		}
	}
	return -1;
}
int main() {
	int testcase, cases = 0;
	int wx, wy, n, x, y;
	scanf("%d", &testcase);
	while (testcase--) {
		state init;
		char label = 'a';
		memset(init.g, ' ', sizeof(init.g));
		scanf("%d %d", &wx, &wy);
		color(init, wx, wy, 1, 2, 'w');
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			color(init, x, y, 2, 1, label);
			label++;
		}
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			color(init, x, y, 3, 1, label);
			label++;
		}
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			color(init, x, y, 1, 2, label);
			label++;
		}
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			color(init, x, y, 1, 3, label);
			label++;
		}
		int ret = bfs(init);
		printf("The minimal number of moves to solve puzzle %d is %d.\n", ++cases, ret);
	}
	return 0;
}
/*
1
2 1
1 4 0
3 1 0 1 3 0 5
2 0 0 4 4
1 5 2

99999
2 0
0
0
0
0
2 1
1 4 0
4 1 0 1 3 0 5 1 4
3 0 0 4 4 3 4
1 5 2
2 1
2 0 2 4 1
4 1 0 1 3 0 5 1 4
2 0 0 4 4
1 5 2

*/
