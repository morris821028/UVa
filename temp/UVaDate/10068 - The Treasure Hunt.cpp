#include <stdio.h> 
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 11;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
char dstr[4][4] = {"E", "W", "S", "N"};
int R, C, N, W[1<<MAXN], WALK;
int Ci[MAXN], Pi[MAXN];
char sg[32][32];
struct State {
	int d, step;
	State* prev;
	void init() {
		d = 0x3f3f3f3f, step = 0, prev = NULL;
	}
};
State dist[20][20][1<<MAXN];
int inq[20][20][1<<MAXN];
void spfa(int sx, int sy, int ex, int ey) {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			for (int k = (1<<N)-1; k >= 0; k--)
				dist[i][j][k].init(), inq[i][j][k] = 0;
		}
	}
	for (int i = (1<<N); i >= 0; i--) {
		int sum = 0;
		for (int j = 0; j < N; j++)
			if ((i>>j)&1)
				sum += Ci[j];
		W[i] = sum;
	}
	
	int tx, ty, ts, ss;
	queue<int> X, Y, S;
	dist[sx][sy][0].d = 0;
	X.push(sx), Y.push(sy), S.push(0);
	while (!X.empty()) {
		sx = X.front(), X.pop();
		sy = Y.front(), Y.pop();
		ss = S.front(), S.pop();
		inq[sx][sy][ss] = 0;
		for (int i = 0; i < 4; i++) {
			tx = sx + dx[i], ty = sy + dy[i], ts = ss;
			if (tx < 0 || ty < 0 || tx >= R || ty >= C)
				continue;
			if (sg[tx][ty] == '#')
				continue;
			if (dist[tx][ty][ts].d > dist[sx][sy][ss].d + W[ss] + WALK) {
				dist[tx][ty][ts].d = dist[sx][sy][ss].d + W[ss] + WALK;
				dist[tx][ty][ts].prev = &dist[sx][sy][ss];
				dist[tx][ty][ts].step = 1<<i;
				if (!inq[tx][ty][ts]) {
					inq[tx][ty][ts] = 1;
					X.push(tx), Y.push(ty), S.push(ts);
				}
			}
			if (sg[tx][ty] >= '0' && sg[tx][ty] <= '9') {
				ts = ss | (1<<(sg[tx][ty] - '0'));
				if (dist[tx][ty][ts].d > dist[sx][sy][ss].d + W[ss] + WALK + Pi[sg[tx][ty] - '0']) {
					dist[tx][ty][ts].d = dist[sx][sy][ss].d + W[ss] + WALK + Pi[sg[tx][ty] - '0'];
					dist[tx][ty][ts].prev = &dist[sx][sy][ss];
					dist[tx][ty][ts].step = (1<<i) | (1<<4);
					if (!inq[tx][ty][ts]) {
						inq[tx][ty][ts] = 1;
						X.push(tx), Y.push(ty), S.push(ts);
					}
				}
			} 

		}
	}
	if (dist[ex][ey][(1<<N)-1].d == 0x3f3f3f3f)
		puts("The hunt is impossible.");
	else {
		printf("Minimum energy required = %d cal\n", dist[ex][ey][(1<<N)-1].d);
		State *ptr = &dist[ex][ey][(1<<N)-1];
		string way = "";
		while (ptr != NULL) {
			if (((ptr->step)>>4)&1)
				way = "P" + way;
			for (int i = 0; i < 4; i++) {
				if (((ptr->step)>>i)&1)
					way = dstr[i] + way;
			}
			ptr = ptr->prev;
		}
		puts(way.c_str());
	}
}
int main() {
	int cases = 0;
	while (scanf("%d %d", &R, &C) == 2 && R) {
		for (int i = 0; i < R; i++)
			scanf("%s", sg[i]);
		scanf("%d", &WALK);
		
		int sx, sy, ex, ey;
		N = 0;
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if (sg[i][j] == '*') {
					sg[i][j] = '0' + N;
					scanf("%d %d", &Pi[N], &Ci[N]);
					N++;
				}
				if (sg[i][j] == 'S')
					sx = i, sy = j;
				if (sg[i][j] == 'T')
					ex = i, ey = j;
			}
		}
		
		printf("Hunt #%d\n", ++cases);
		spfa(sx, sy, ex, ey);
		puts("");
	}
	return 0;
}
/*
5 8
#......T
..#*..#.
..######
...*...#
####S.#*
5
10 50 50 100 30 80
10 10
#........*
..#*..#...
..######..
.......#..
####S..##.
.*.#...#..
.......#..
.##.#....#
.*.....#.#
....*..#.T
10
100 400 20 50 150 250 30 70 4 5

20 20
....................
.*..................
..........*.........
....................
....................
............*.......
....................
....................
..............*.....
.........S..........
....................
..............*.....
....................
....................
..*..........*......
....................
..........T.........
..*.................
....................
.....*......*.......
5
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
*/
