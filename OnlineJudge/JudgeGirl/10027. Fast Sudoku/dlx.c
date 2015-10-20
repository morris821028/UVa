#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAXN 262144
#define MAXR 1024
typedef struct {
    int left, right, up, down;
    int data, ch, rh;
} Node;
// DLX header
typedef struct {
	void (* const init) (int);
	void (* const newrow) (int, int[], int, int);
	void (* const solve) (int);
} DLX_namespace;
// DLX body begin
Node DL[MAXN + MAXR];
int s[MAXR], o[MAXR], head, size, ans;
void DLX_remove(int c) {
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
void DLX_resume(int c) {
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
void DLX_debug(int n) {
	static int set[81];
	puts("--");
    for (int i = 0; i < n; i++)
        set[DL[o[i]].data] = DL[o[i]].rh+1;
    for (int i = 0; i < 9; i++, puts(""))
        for (int j = 0; j < 9; j++)
            printf("%d ", set[i*9+j]);
}
void DLX_dfs(int k) {
    if (DL[head].right == head) {
        ans++;
//        DLX_debug(k);
        return;
    }
    int t = INT_MAX, c, i, j;
    for (i = DL[head].right; i != head; i = DL[i].right) {
        if (s[i] < t) {
            t = s[i], c = i;
        }
    }
    DLX_remove(c);
    for (int i = DL[c].down; i != c; i = DL[i].down) {
        o[k] = i;
        for (int j = DL[i].right; j != i; j = DL[j].right)
            DLX_remove(DL[j].ch);
        DLX_dfs(k+1);
        for (int j = DL[i].left; j != i; j = DL[j].left)
            DLX_resume(DL[j].ch);
    }
    DLX_resume(c);
}
int DLX_newnode(int up, int down, int left, int right) {
    DL[size].up = up, DL[size].down = down;
    DL[size].left = left, DL[size].right = right;
    DL[up].down = DL[down].up = DL[left].right = DL[right].left = size;
    return size++;
}
void DLX_newrow(int n, int Row[], int rh, int set) {
    int a, r, row = -1, k;
    for (a = 0; a < n; a++) {
        r = Row[a];
        DL[size].ch = r, DL[size].data = set, s[r]++;
        if (row == -1) {
            row = DLX_newnode(DL[DL[r].ch].up, DL[r].ch, size, size);
            DL[row].rh = rh;
        } else {
            k = DLX_newnode(DL[DL[r].ch].up, DL[r].ch, DL[row].left, row);
            DL[k].rh = rh;
        }
    }
}
void DLX_init(int m) {
    size = 0;
    head = DLX_newnode(0, 0, 0, 0);
    for (int i = 1; i <= m; i++) {
        DLX_newnode(i, i, DL[head].left, head);
        DL[i].ch = i, s[i] = 0;
    }
}
DLX_namespace const DLX = {DLX_init, DLX_newrow, DLX_dfs};
// DLX body end
int main() {
    int g[10][10], row[10];
    int n = 9, m = n*n*4, tn = 3;
    DLX.init(m);
    for (int i = 0; i < n; i++) {
    	for (int j = 0; j < n; j++) {
    		scanf("%d", &g[i][j]);
    		if (g[i][j] == 0) {
    			for (int k = 0; k < n; k++) {
    				int t = 0;
                    row[t++] = 0 + i*n + j + 1;
                    row[t++] = n*n + i*n + k + 1;
                    row[t++] = 2*n*n+ j*n + k + 1;
                    row[t++] = 3*n*n+ (i/tn*tn + j/tn)*n + k + 1;
                    DLX.newrow(t, row, k, i*n+j);
				}
			} else {
				int k = g[i][j]-1, t = 0;
                row[t++] = i*n + j + 1;
                row[t++] = n*n + i*n + k + 1;
                row[t++] = 2*n*n+ j*n + k + 1;
                row[t++] = 3*n*n+ (i/tn*tn + j/tn)*n + k + 1;
                DLX.newrow(t, row, k, i*n+j);
			}
		}
	}
    ans = 0, DLX.solve(0);
    printf("%d\n", ans);
    return 0;
}
