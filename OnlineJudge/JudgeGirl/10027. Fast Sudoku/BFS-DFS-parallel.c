#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>
#define MAXN 8192
#define MAXR 1024
typedef unsigned char byte;

// parallel utils
typedef struct {
	byte b[9][9];			// board
	int r[9], c[9], g[9];	// row, column, grid
} Board;
static inline int gridID(int x, int y) {
	return x / 3 * 3 + y / 3;
}
void board_init(Board *b) {
	memset(b, 0, sizeof(Board));
}
inline bool board_test(const Board *b, int x, int y, int v) {
	return b->b[x][y] == 0 && ((b->r[x]>>(v-1))&1) == 0 && ((b->c[y]>>(v-1))&1) == 0 && ((b->g[gridID(x, y)]>>(v-1))&1) == 0;
}
inline bool board_fill(Board *b, int x, int y, int v) {
	b->b[x][y] = v;
	b->r[x] |= 1<<(v-1);
	b->c[y] |= 1<<(v-1);
	b->g[gridID(x, y)] |= 1<<(v-1);
}
inline void board_undo(Board *b, int x, int y, int v) {
	b->b[x][y] = 0;
	b->r[x] ^= 1<<(v-1);
	b->c[y] ^= 1<<(v-1);
	b->g[gridID(x, y)] ^= 1<<(v-1);
}

int search_sudoku(Board *b, int C[][2], int idx) {
	if (idx == -1)	return 1;
	int ret = 0;
	int x = C[idx][0], y = C[idx][1];
	for (int i = 1; i <= 9; i++) {
		if (!board_test(b, x, y, i))
			continue;
		board_fill(b, x, y, i);
		ret += search_sudoku(b, C, idx-1);
		board_undo(b, x, y, i);
	}
	return ret;
}
int sudoku(Board board) {
	int C[81][2], m = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (board.b[i][j] == 0)
				C[m][0] = i, C[m][1] = j, m++;
		}
	}
	
	return search_sudoku(&board, C, m-1);
}
int incomplete_bfs(int g[][9]) {
	Board origin;
	int n = 9;
	int A[81][2], m = 0;
	board_init(&origin);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (g[i][j]) {
				board_fill(&origin, i, j, g[i][j]);
			} else {
				A[m][0] = i, A[m][1] = j, m++;
			}
		}
	}
#define MAXQMEM 100000
	static Board Q[2][MAXQMEM];
	int Qcnt[2] = {}, Qflag = 0;
	Q[Qflag][Qcnt[Qflag]] = origin, Qcnt[Qflag]++;
	for (int it = 0; it < m; it++) {
		const int x = A[it][0], y = A[it][1];
		Qcnt[!Qflag] = 0;
		for (int i = 0; i < Qcnt[Qflag]; i++) {
			for (int j = 1; j <= 9; j++) {
				if (!board_test(&Q[Qflag][i], x, y, j))
					continue;
				int pIdx;
				#pragma omp critical
				{
					pIdx = Qcnt[!Qflag]++;
				}
				if (pIdx >= MAXQMEM)
					break;
				Q[!Qflag][pIdx] = Q[Qflag][i];
				board_fill(&Q[!Qflag][pIdx], x, y, j);
			}
		}
		if (Qcnt[!Qflag] >= MAXQMEM) {
			int ret = 0;
			#pragma omp parallel for reduction(+:ret) schedule(guided)
			for (int i = 0; i < Qcnt[Qflag]; i++) {
				ret += sudoku(Q[Qflag][i]);
			}
			return ret;
		}
		Qflag = !Qflag;
	}
	return Qcnt[Qflag];
}
int main() {
    int g[9][9], n = 9;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &g[i][j]);
    
    int ret = incomplete_bfs(g);
    printf("%d\n", ret);
    return 0;
} 
