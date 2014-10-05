#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;

#define MAXN 10
#define MAXM 15
int M[] = {10, 24, 15, 24};
int B[4][32], OK[4][32];
int color[MAXN][MAXM] = {}, used[MAXN][MAXM] = {};
int inBound(int x, int y) {
	return x >= 0 && y >= 0 && x < MAXN && y < MAXM;
}
void fillColor(int tx, int ty, int dx, int dy, int c) {
	for (; inBound(tx, ty); tx += dx, ty += dy) {
		if (!used[tx][ty]) {
			used[tx][ty] = 1;
			color[tx][ty] = c;
		}
	}
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int cond = 0, sat = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < M[i]; j++)
				scanf("%d", &B[i][j]);
			cond += M[i];
		}
		memset(color, 0, sizeof(color));
		memset(used, 0, sizeof(used));
		memset(OK, 0, sizeof(OK));
		int update = 0;
		do {
			update = 0;
			// section 1
			for (int i = 0; i < M[0]; i++) {
				int t = 0, s = B[0][i], b = 0, w = 0;
				for (int j = 0; j < MAXM; j++) {
					if (used[i][j]) {
						if (color[i][j] == 0)	w++;
						else					b++;
					}
					t++;
				}
				if (w + b == t && s == b)	OK[0][i] = 1;
				if (w + b != t) {
					if (s == b + (t - w - b)) { // color black
						fillColor(i, 0, 0, 1, 1);
						update = 1;
					}
					if (t - s == w + (t - w - b)) {
						fillColor(i, 0, 0, 1, 0);
						update = 1;
					}
				}
			}
			// section 2
			for (int i = 0; i < M[1]; i++) {
				int t = 0, s = B[1][i], b = 0, w = 0;
				int sx, sy, tx, ty;
				if (i < 10)	sx = i, sy = 0;
				else		sx = MAXN - 1, sy = i - MAXN + 1;
				for (tx = sx, ty = sy; inBound(tx, ty); tx--, ty++) {
					if (used[tx][ty]) {
						if (color[tx][ty] == 0)	w++;
						else					b++;
					}
					t++;
				}
				if (w + b == t && s == b)	OK[1][i] = 1;
				if (w + b != t) {
					if (s == b + (t - w - b)) { // color black
						fillColor(sx, sy, -1, 1, 1);
						update = 1;
					}
					if (t - s == w + (t - w - b)) {
						fillColor(sx, sy, -1, 1, 0);
						update = 1;
					}
				}
			}
			// section 3
			for (int i = 0; i < M[2]; i++) {
				int t = 0, s = B[2][i], b = 0, w = 0;
				for (int j = 0; j < MAXN; j++) {
					if (used[j][i]) {
						if (color[j][i] == 0)	w++;
						else					b++;
					}
					t++;
				}
				if (w + b == t && s == b)	OK[2][i] = 1;
				if (w + b != t) {
					if (s == b + (t - w - b)) { // color black
						fillColor(0, i, 1, 0, 1);
						update = 1;
					}
					if (t - s == w + (t - w - b)) {
						fillColor(0, i, 1, 0, 0);
						update = 1;
					}
				}
			}
			// section 4
			for (int i = 0; i < M[3]; i++) {
				int t = 0, s = B[3][i], b = 0, w = 0;
				int sx, sy, tx, ty;
				if (i < MAXM)	sx = MAXN - 1, sy = i;
				else			sx = MAXN - (i - MAXM) - 2, sy = MAXM - 1;
				for (tx = sx, ty = sy; inBound(tx, ty); tx--, ty--) {
					if (used[tx][ty]) {
						if (color[tx][ty] == 0)	w++;
						else					b++;
					}
					t++;
				}
				if (w + b == t && s == b)	OK[3][i] = 1;
				if (w + b != t) {
					if (s == b + (t - w - b)) { // color black
						fillColor(sx, sy, -1, -1, 1);
						update = 1;
					}
					if (t - s == w + (t - w - b)) {
						fillColor(sx, sy, -1, -1, 0);
						update = 1;
					}
				}
			}
		} while (update);
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < M[i]; j++)
				sat += OK[i][j];
		if (cond == sat) {
			for (int i = 0; i < MAXN; i++, puts("")) {
				for (int j = 0; j < MAXM; j++) {
					printf("%c", color[i][j] ? '#' : '.');
				}
			}
		} else {
			for (int i = 0; i < MAXN; i++, puts("")) {
				for (int j = 0; j < MAXM; j++) {
					printf(".");
				}
			}
		}
		if (testcase)	puts("");
	}
	return 0;
}
/*
2
10 10 6 4 6 8 13 15 11 6
0 1 2 2 2 2 4 5 5 6 7 6 5 6 6 5 5 6 6 3 2 2 1 0
2 4 5 5 7 6 7 10 10 10 7 3 3 5 5
0 0 1 3 4 4 4 4 3 4 5 7 8 8 9 9 6 4 4 2 0 0 0 0
*/
