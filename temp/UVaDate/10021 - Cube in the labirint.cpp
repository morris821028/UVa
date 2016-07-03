#include <stdio.h> 
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
int g[16][16][4];
int X, Y, A, B, C, D;

struct Cube {
	int x, y, face[6]; // [down, front, up, back, left, right]
	Cube(int a = 0, int b = 0):
		x(a), y(b) {
		for (int i = 0; i < 6; i++)
			face[i] = i;
	}
	Cube roll(int dir) {
		Cube r = (*this);
		int t;
		if (dir == 0) { // roll right
			t = r.face[0];
			r.face[0] = r.face[5], r.face[5] = r.face[2], r.face[2] = r.face[4];
			r.face[4] = t;
		} else if (dir == 1) { // roll left
			t = r.face[0];
			r.face[0] = r.face[4], r.face[4] = r.face[2], r.face[2] = r.face[5];
			r.face[5] = t;
		} else if (dir == 2) { // roll up
			t = r.face[0];
			r.face[0] = r.face[3], r.face[3] = r.face[2], r.face[2] = r.face[1];
			r.face[1] = t;
		} else if (dir == 3) { // roll down
			t = r.face[0];
			r.face[0] = r.face[1], r.face[1] = r.face[2], r.face[2] = r.face[3];
			r.face[3] = t;
		}
		r.x += dx[dir], r.y += dy[dir];
		return r;
	}
};
void bfs() {
	int dist[16][16][16][16] = {};
	queue<Cube> Q;
	Cube u(A, B), v;
	Q.push(u), dist[u.x][u.y][u.face[0]][u.face[1]] = 0;
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		if (u.x == C && u.y == D && u.face[0] == 0) {
			printf("%d\n", dist[C][D][0][u.face[1]]);
			return ;
		}
		for (int i = 0; i < 4; i++) {
			if (g[u.x][u.y][i] == 0) {
				v = u.roll(i);
				if (v.x <= 0 || v.x > X || v.y <= 0 || v.y > Y)
					continue;
				if (dist[v.x][v.y][v.face[0]][v.face[1]] == 0) {
					dist[v.x][v.y][v.face[0]][v.face[1]] = dist[u.x][u.y][u.face[0]][u.face[1]] + 1;
					Q.push(v);
				}
			}
		}
	}
	puts("No solution");
}
int main() {   
	int testcase;
	char s[1024];
	
	scanf("%d", &testcase);
	while (testcase--) {
		memset(g, 0, sizeof(g));
		scanf("%d %d %d %d %d %d", &X, &Y, &A, &B, &C, &D);
		while (getchar() != '\n');
		
		int kind;
		while (gets(s)) {
			if (s[0] == '\0')	break;
			if (s[0] == 'v')		kind = 0;
			else if (s[0] == 'h')	kind = 1;
			else {
				int x, y;
				sscanf(s, "%d %d", &x, &y);
				if (kind == 0) {
					g[x][y][2] = g[x+1][y][3] = 1;
				} else {
					g[x][y][0] = g[x][y+1][1] = 1;
				}
			}
		}
		
		bfs();
		if (testcase)
			puts("");
	}
	return 0;
}
/*
999

10 2
1 1
10 1
v
2 1
6 2
h
4 1

10 3
1 1
5 2
v
4 2
5 2
h
5 2
5 1

3 2
1 1
2 2
*/
