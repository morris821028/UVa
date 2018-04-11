#include <bits/stdc++.h> 
using namespace std;

class DLX {
    public:
    static const int MAXCL = 256;
	static const int MAXDL = 131072 + 256;
    struct DancingLinks {
        int left, right, up, down, ch;
        int id;
    } DL[MAXDL];
    int s[MAXCL], o[MAXCL], head, size;		
    void remove(int c) {
        DL[DL[c].right].left = DL[c].left;
        DL[DL[c].left].right = DL[c].right;
        int i, j;
        for (i = DL[c].down; i != c; i = DL[i].down) {
            for (j = DL[i].right; j != i; j = DL[j].right) {
                DL[DL[j].down].up = DL[j].up;
                DL[DL[j].up].down = DL[j].down;
                s[DL[j].ch]--;
            }
        }
    }
    void resume(int c) {
        int i, j;
        for (i = DL[c].down; i != c; i = DL[i].down) {
            for (j = DL[i].left; j != i; j = DL[j].left) {
                DL[DL[j].down].up = j;
                DL[DL[j].up].down = j;
                s[DL[j].ch]++;
            }
        }
        DL[DL[c].right].left = c;
        DL[DL[c].left].right = c;
    }
    int ret[128];
    void dfs(int dep, int remain) {
        ret[dep + remain] = 1;
        if (DL[head].right == head)
            return;
        int tmp = 0, c, i, j;
        // special: pick the maximum options column
        for (i = DL[head].right; i != head; i = DL[i].right)
            if (s[i] > tmp)
                tmp = s[i], c = i;
        // not always exists exact cover
        if (tmp == 0)
        	return ;
        remove(c);
        for (i = DL[c].down; i != c; i = DL[i].down) {
            for (j = DL[i].right; j != i; j = DL[j].right)
                remove(DL[j].ch);
            dfs(dep+1, remain - DL[i].id);
            for (j = DL[i].left; j != i; j = DL[j].left)
                resume(DL[j].ch);
        }
        resume(c);
    }
    int newNode(int u, int d, int l, int r) {
        DL[size].up = u, DL[size].down = d;
        DL[size].left = l, DL[size].right = r;
        DL[u].down = DL[d].up = DL[l].right = DL[r].left = size;
        assert(size < MAXDL);
        return size++;
    }
    void newRow(int r[], int rn, int id) {
        int i, j, h;
        for (i = 0; i < rn; i++) {
            DL[size].ch = r[i], s[r[i]]++;
            DL[size].id = id; // extra data
            if (i) {
                j = newNode(DL[DL[r[i]].ch].up, DL[r[i]].ch, DL[h].left, h);
            } else {
                h = newNode(DL[DL[r[i]].ch].up, DL[r[i]].ch, size, size);
            }
        }
    }
    void init(int c) {// total column
        size = 0;
        head = newNode(0, 0, 0, 0);
        for (int i = 1; i <= c; i++) {
            newNode(i, i, DL[head].left, head);
            DL[i].ch = i, s[i] = 0;
        }
    }
} DLX;

int main() {
	int cases = 0;
	int a, b, c, m;
	while (scanf("%d %d %d %d", &a, &b, &c, &m) == 4 && a) {
		int8_t g[20][20][20] = {};
		int8_t ig[20][20][20] = {}, cg[20][20][20] = {};
		for (int i = 0; i < m; i++) {
			int x, y, z;
			scanf("%d %d %d", &x, &y, &z);
			x--, y--, z--;
			g[x][y][z] = -1;
		}
	
		int col = 0, tot = 0;
		for (int i = 0; i < a; i++) {
			for (int j = 0; j < b; j++) {
				for (int k = 0; k < c; k++) {
					if (g[i][j][k] == 0)
						tot++;
				}
			}
		}
		
		for (int i = 0; i < a; i++) {
			for (int j = 0; j < b; j++) {
				for (int k = 0; k < c; k++) {
					if (g[i][j][k] == -1)
						continue;
					int8_t t = 1;
					if (i && j && k) {
						t = g[i-1][j-1][k-1];
						t = min(t, g[i-1][j-1][k]);
						t = min(t, g[i-1][j][k-1]);
						t = min(t, g[i-1][j][k]);
						t = min(t, g[i][j-1][k-1]);
						t = min(t, g[i][j-1][k]);
						t = min(t, g[i][j][k-1]);
						if (t < 0)
							t = 1;
						else
							t++;
					}
					g[i][j][k] = t;
					if (t > 1) {
						for (int p = 0; p < t; p++) {
							for (int q = 0; q < t; q++) {
								for (int r = 0; r < t; r++)
									cg[i-p][j-q][k-r] = 1;
							}
						}
					}
				}
			}
		}
		
		for (int i = 0; i < a; i++) {
			for (int j = 0; j < b; j++) {
				for (int k = 0; k < c; k++) {
					if (cg[i][j][k] == 1)
						ig[i][j][k] = ++col;
				}
			}
		}
		assert(col < 128);
		DLX.init(col);
		
		for (int i = 0; i < a; i++) {
			for (int j = 0; j < b; j++) {
				for (int k = 0; k < c; k++) {
					if (g[i][j][k] < 2)
						continue;
					int t = g[i][j][k];
					static int row[128];
					for (int it = t; it >= 2; it--) {
						int row_cnt = 0;
						for (int p = 0; p < it; p++) {
							for (int q = 0; q < it; q++) {
								for (int r = 0; r < it; r++)
									row[row_cnt++] = ig[i-p][j-q][k-r];
							}
						}
						DLX.newRow(row, row_cnt, it*it*it);
					}
				}
			}
		}
		memset(DLX.ret, 0, sizeof(DLX.ret));
		DLX.dfs(0, tot);
		printf("Case %d:", ++cases);
		for (int i = 1; i <= tot; i++) {
			if (DLX.ret[i])
				printf(" %d", i);
		}
		puts("");
		fflush(stdout);
	}
	return 0;
}
/*
2 2 3 0
2 2 3 2
1 1 1
2 2 3
4 5 5 0
5 5 5 0
20 2 3 0
0 0 0 0
*/
