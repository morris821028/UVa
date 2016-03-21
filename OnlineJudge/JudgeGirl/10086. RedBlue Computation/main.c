#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 1024
#define C_WHITE 0
#define C_RED   1
#define C_BLUE  2

char g1[MAXN][MAXN], g2[MAXN][MAXN];

void moveRed(int n) {
	int chunk = 8;
	#pragma omp parallel for schedule(static, chunk)
	for (int i = 0; i < n; i++)
		memset(g2[i], C_WHITE, sizeof(char) * n);
	#pragma omp parallel for schedule(static, chunk)
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (g1[i][j] == C_BLUE) {
				g2[i][j] = C_BLUE;
			} else if (g1[i][j] == C_RED) {
				int next = j+1 == n ? 0 : j+1;
				if (g1[i][next] == C_WHITE)
					g2[i][next] = C_RED;
				else
					g2[i][j] = C_RED;
			}
		}
	}
}
void moveBlue(int n) {
	int chunk = 8;
	#pragma omp parallel for schedule(static, chunk)
	for (int i = 0; i < n; i++)
		memset(g1[i], C_WHITE, sizeof(char) * n);
	#pragma omp parallel for schedule(static, chunk)
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (g2[i][j] == C_RED) {
				g1[i][j] = C_RED;
			} else if (g2[i][j] == C_BLUE) {
				int next = i+1 == n ? 0 : i+1;
				if (g2[next][j] == C_WHITE)
					g1[next][j] = C_BLUE;
				else
					g1[i][j] = C_BLUE;
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
static void printBoard(int n) {
	char color[4] = "WRB";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			putchar(color[g1[i][j]]);
		putchar('\n');
	}
}
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; i++) {
			scanf("%s", &g1[i]);
			for (int j = 0; j < n; j++)
				g1[i][j] = toIndex(g1[i][j]);
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

