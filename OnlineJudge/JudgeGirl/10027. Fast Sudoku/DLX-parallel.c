#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>
#define MAXN 8192
#define MAXR 1024
typedef unsigned char byte;
typedef struct {
    int left, right, up, down;
    int ch;
} Node;
// DLX header
typedef struct {
    int (* const sudoku) (byte [][9]);
} DLX_namespace;
// DLX body begin
void DLX_remove(int c, Node DL[], int s[]) {
    DL[DL[c].right].left = DL[c].left;
    DL[DL[c].left].right = DL[c].right;
    for (int i = DL[c].down; i != c; i = DL[i].down) {
        for (int j = DL[i].right; j != i; j = DL[j].right) {
            DL[DL[j].down].up = DL[j].up;
            DL[DL[j].up].down = DL[j].down;
            s[DL[j].ch]--;
        }
    }
}
void DLX_resume(int c, Node DL[], int s[]) {
    for (int i = DL[c].down; i != c; i = DL[i].down) {
        for (int j = DL[i].left; j != i; j = DL[j].left) {
            DL[DL[j].down].up = j;
            DL[DL[j].up].down = j;
            s[DL[j].ch]++;
        }
    }
    DL[DL[c].right].left = c;
    DL[DL[c].left].right = c;
}
int DLX_dfs(int k, Node DL[], int s[], int head) {
	if (DL[head].right == head)
        return 1;
    int t = INT_MAX, c;
    for (int i = DL[head].right; i != head; i = DL[i].right) {
        if (s[i] < t) {
            t = s[i], c = i;
        }
    }
    int ans = 0;
    DLX_remove(c, DL, s);
    for (int i = DL[c].down; i != c; i = DL[i].down) {
        for (int j = DL[i].right; j != i; j = DL[j].right)
            DLX_remove(DL[j].ch, DL, s);
        ans += DLX_dfs(k+1, DL, s, head);
        for (int j = DL[i].left; j != i; j = DL[j].left)
            DLX_resume(DL[j].ch, DL, s);
    }
    DLX_resume(c, DL, s);
	return ans;
}
int DLX_newnode(int up, int down, int left, int right, Node DL[], int *size) {
    DL[*size].up = up, DL[*size].down = down;
    DL[*size].left = left, DL[*size].right = right;
    DL[up].down = DL[down].up = DL[left].right = DL[right].left = *size;
    assert(*size < MAXN);
    return (*size)++;
}
void DLX_newrow(int n, int Row[], Node DL[], int s[], int *size) {
    int a, r, row = -1, k;
    for (a = 0; a < n; a++) {
        r = Row[a];
        DL[*size].ch = r, s[r]++;
        if (row == -1) {
            row = DLX_newnode(DL[DL[r].ch].up, DL[r].ch, *size, *size, DL, size);
        } else {
            k = DLX_newnode(DL[DL[r].ch].up, DL[r].ch, DL[row].left, row, DL, size);
        }
    }
}
void DLX_init(int m, Node DL[], int s[], int *size, int *head) {
    *size = 0;
    *head = DLX_newnode(0, 0, 0, 0, DL, size);
    for (int i = 1; i <= m; i++) {
        DLX_newnode(i, i, DL[*head].left, *head, DL, size);
        DL[i].ch = i, s[i] = 0;
    }
}
int DLX_sudoku(byte g[][9]) {
	Node DL[MAXN + MAXR];
	int s[MAXR], head, size;
    int row[10];
    int used[4][10][10] = {}, isValid = 1;
    int n = 9, tn = 3;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (g[i][j]) {
            	int x = g[i][j];
            	int y = i/3*3 + j/3;
            	if (used[1][i][x])	isValid = 0;
            	if (used[2][j][x])	isValid = 0;
            	if (used[3][y][x])	isValid = 0;
            	used[0][i][j] = 1;
            	used[1][i][x] = used[2][j][x] = used[3][y][x] = 1;
			}
        }
    }
    if (!isValid)
    	return 0;
	
    int OFF[4] = {};
    int label[4][10][10] = {};
    for (int i = 0; i < n; i++) {
    	for (int j = 0; j < n; j++) {
    		if (used[0][i][j] == 0)
    			label[0][i][j] = ++OFF[0];
		}
	}
	for (int k = 1; k < 4; k++) {
		OFF[k] = OFF[k-1];
		for (int i = 0; i < n; i++) {
			for (int j = 1; j <= n; j++) {
				if (used[k][i][j] == 0) {
					label[k][i][j] = ++OFF[k];
				}
			}
		}
	}
    DLX_init(OFF[3], DL, s, &size, &head);
    for (int i = 0; i < n; i++) {
    	for (int j = 0; j < n; j++) {
    		if (g[i][j])	continue;
    		for (int k = 1; k <= n; k++) {
    			int x = k;
            	int y = i/3*3 + j/3;
            	if (used[1][i][x])	continue;
            	if (used[2][j][x])	continue;
            	if (used[3][y][x])	continue;
    			
    			row[0] = label[0][i][j];
    			row[1] = label[1][i][k];
    			row[2] = label[2][j][k];
    			row[3] = label[3][y][k];
    			DLX_newrow(4, row, DL, s, &size);
			}
		}
	}
    return DLX_dfs(0, DL, s, head);
}
DLX_namespace const DLX = {DLX_sudoku};
// DLX body end

// parallel utils
typedef struct {
	byte b[9][9];	// board
	bool r[9][9], c[9][9], g[9][9];	// row, column, grid
} Board;
static inline int gridID(int x, int y) {
	return x / 3 * 3 + y / 3;
}
void board_init(Board *b) {
	memset(b, 0, sizeof(Board));
}
bool board_test(const Board *b, int x, int y, int v) {
	return b->b[x][y] == 0 && b->r[x][v-1] == 0 && b->c[y][v-1] == 0 && b->g[gridID(x, y)][v-1] == 0;
}
bool board_fill(Board *b, int x, int y, int v) {
	b->b[x][y] = v;
	b->r[x][v-1] = b->c[y][v-1] = b->g[gridID(x, y)][v-1] = 1;
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
#define MAXQMEM 8192
	static Board Q[2][MAXQMEM*9];
	int Qcnt[2] = {}, Qflag = 0;
	Q[Qflag][Qcnt[Qflag]] = origin, Qcnt[Qflag]++;
	for (int it = 0; it < m; it++) {
		const int x = A[it][0], y = A[it][1];
		Qcnt[!Qflag] = 0;
		#pragma omp parallel for
		for (int i = 0; i < Qcnt[Qflag]; i++) {
			for (int j = 1; j <= 9; j++) {
				if (!board_test(&Q[Qflag][i], x, y, j))
					continue;
				int pIdx;
				#pragma omp critical
				{
					pIdx = Qcnt[!Qflag]++;
				}
				Q[!Qflag][pIdx] = Q[Qflag][i];
				board_fill(&Q[!Qflag][pIdx], x, y, j);
			}
		}
		if (Qcnt[!Qflag] >= MAXQMEM) {
			int ret = 0;
			#pragma omp parallel for reduction(+:ret)
			for (int i = 0; i < Qcnt[Qflag]; i++) {
				ret += DLX.sudoku(Q[Qflag][i].b);
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
