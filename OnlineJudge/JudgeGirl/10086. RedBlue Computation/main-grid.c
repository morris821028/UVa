#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#define MAXN 1024
#define C_WHITE 0
#define C_RED   1
#define C_BLUE  2
#define MAXTHREAD 4
#define MAXGAPX 512
#define MAXGAPY 512

char g1[MAXTHREAD][MAXGAPX * MAXGAPY];
char g2[MAXTHREAD][MAXGAPX * MAXGAPY];
char g[MAXN][MAXN];

#define min(x, y) ((x) < (y) ? (x) : (y))
typedef struct BlockInfo {
	int bx, by, nx, ny;
} BlockInfo;
BlockInfo info[4];
static inline char* elemInst(char (*g)[MAXGAPX*MAXGAPY], int x, int y, int n) {
	n >>= 1;
	int id = (x/n)*2 + (y/n);
	return &g[id][(x-info[id].bx)*info[id].ny + (y-info[id].by)];
}
static void printBoard(int n) {
	char color[4] = "WRB";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			putchar(color[*elemInst(g1, i, j, n)]);
		putchar('\n');
	}
}
void clearGrid(int n, int gid) {
	int chunk = 1;
	#pragma omp parallel for schedule(static, chunk)	
	for (int i = 0; i < MAXTHREAD; i++) {
		int lx = n * (i/2) / 2;
		int ly = n * (i%2) / 2;
		int rx = n * (i/2 + 1) / 2 - 1;
		int ry = n * (i%2 + 1) / 2 - 1;
		info[i].bx = lx, info[i].by = ly;
		info[i].nx = rx - lx + 1;
		info[i].ny = ry - ly + 1;
		
		char (*gpt)[MAXGAPX * MAXGAPY];
		if (gid == 1)
			gpt = g1[i];
		else
			gpt = g2[i];
		memset(gpt, 0, sizeof(char) * (info[i].nx * info[i].ny));
	}
}
void moveRed(int n) {
	clearGrid(n, 2);
	int chunk = 1;
	#pragma omp parallel for schedule(static, chunk) firstprivate(n)
	for (int i = 0; i < MAXTHREAD; i++) {
		for (int x = info[i].bx, ix = 0; ix < info[i].nx; x++, ix++) {
			for (int y = info[i].by, iy = 0; iy < info[i].ny; y++, iy++) {
				if (*elemInst(g1, x, y, n) == C_BLUE) {
					*elemInst(g2, x, y, n) = C_BLUE;
				} else if (*elemInst(g1, x, y, n) == C_RED) {
					int next = y+1 == n ? 0 : y+1;
					if (*elemInst(g1, x, next, n) == C_WHITE)
						*elemInst(g2, x, next, n) = C_RED;
					else
						*elemInst(g2, x, y, n) = C_RED;
				}
			}
		}
	}
}
void moveBlue(int n) {
	clearGrid(n, 1);
	int chunk = 1;
	#pragma omp parallel for schedule(static, chunk) firstprivate(n)
	for (int i = 0; i < MAXTHREAD; i++) {
		for (int x = info[i].bx, ix = 0; ix < info[i].nx; x++, ix++) {
			for (int y = info[i].by, iy = 0; iy < info[i].ny; y++, iy++) {
				if (*elemInst(g2, x, y, n) == C_RED) {
					*elemInst(g1, x, y, n) = C_RED;
				} else if (*elemInst(g2, x, y, n) == C_BLUE) {
					int next = x+1 == n ? 0 : x+1;
					if (*elemInst(g2, next, y, n) == C_WHITE)
						*elemInst(g1, next, y, n) = C_BLUE;
					else
						*elemInst(g1, x, y, n) = C_BLUE;
				}
			}
		}
	}
}
static inline int toIndex(char c) {
	if (c == 'W')	return C_WHITE;
	if (c == 'R')	return C_RED;
	if (c == 'B')	return C_BLUE;
	fprintf(stderr, "[WARNING] %s %d\n", __FILE__, __LINE__);
}

int main() {
	
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		clearGrid(n, 1);
		for (int i = 0; i < n; i++) {
			scanf("%s", &g[i]);
			for (int j = 0; j < n; j++)
				g[i][j] = toIndex(g[i][j]);
			for (int j = 0; j < n; j++)
				*elemInst(g1, i, j, n) = g[i][j];
		}
				
		for (int it = 0; it < m; it++) {
			moveRed(n);
			moveBlue(n);
		}
		printBoard(n);
	}
	return 0;
}
/*
4 1
RRWR
WWBW
BWRW
WWWW
*/

