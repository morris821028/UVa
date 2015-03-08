#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;
#define MAXV 0x3f3f3f3f
#define MAXE 1048576
#define MAXC 1048576
#define MAXR 65536
class DLX {
public:
    struct DacingLinks {
        int left, right;
        int up, down;
        int ch, rh;
        int data; // extra info
    } DL[MAXE];
    int s[MAXC], o[MAXR], head, size, Ans, findflag;
    void Remove(int c) {
        static int i;
        for(i = DL[c].down; i != c; i = DL[i].down) {
            DL[DL[i].right].left = DL[i].left;
            DL[DL[i].left].right = DL[i].right;
            s[DL[i].ch]--;
        }
    }
    void Resume(int c) {
        static int i;
        for(i = DL[c].down; i != c; i = DL[i].down) {
            DL[DL[i].right].left = i;
            DL[DL[i].left].right = i;
            s[DL[i].ch]++;
        }
    }
    int used[MAXC] = {};
    int H() {
        static int c, ret, i, j, time = 0;
        for(c = DL[head].right, ++time, ret = 0; c != head; c = DL[c].right) {
            if(used[c] != time) {
                ret ++, used[c] = time;
                for(i = DL[c].down; i != c; i = DL[i].down)
                    for(j = DL[i].right; j != i; j = DL[j].right)
                        used[DL[j].ch] = time;
            }
        }
        return ret;
    }
    void DFS(int k) {
        if(k + H() >= Ans) return;
        if(DL[head].right == head) {
            Ans = min(Ans, k);
            return;
        }
        int t = MAXV, c = 0, i, j;
        for(i = DL[head].right; i != head; i = DL[i].right) {
            if(s[i] < t) {
                t = s[i], c = i;
            }
        }
        for(i = DL[c].down; i != c; i = DL[i].down) {
            o[k] = i;
            Remove(i);
            for(j = DL[i].right; j != i; j = DL[j].right) Remove(j);
            DFS(k+1);
            for(j = DL[i].left; j != i; j = DL[j].left) Resume(j);
            Resume(i);
            if (findflag) break;
        }
    }
    int new_node(int up, int down, int left, int right) {
        assert(size < MAXE);
        DL[size].up = up, DL[size].down = down;
        DL[size].left = left, DL[size].right = right;
        DL[up].down = DL[down].up = DL[left].right = DL[right].left = size;
        return size++;
    }
    void addrow(int n, int Row[], int data) {
        int a, r, row = -1, k;
        for(a = 0; a < n; a++) {
            r = Row[a];
            DL[size].ch = r, s[r]++;
            DL[size].data = data;
            if(row == -1) {
                row = new_node(DL[DL[r].ch].up, DL[r].ch, size, size);
                DL[row].rh = a;
            }else {
                k = new_node(DL[DL[r].ch].up, DL[r].ch, DL[row].left, row);
                DL[k].rh = a;
            }
        }
    }
    void init(int m) {
        size = 0;
        head = new_node(0, 0, 0, 0);
        int i;
        for(i = 1; i <= m; i++) {
            new_node(i, i, DL[head].left, head);
            DL[i].ch = i, s[i] = 0;
        }
    }
} dlx;
const int dx[8] = {0, 0, 1, 1, 1, -1, -1, -1};
const int dy[8] = {1, -1, 0, 1, -1, 0, 1, -1};
int greedy(int n, int m, char g[][16]) {
    int ret = 0;
    while (true) {
        int has = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (g[i][j] == 'X') {
                    has = 1;
                }
            }
        }
        if (!has)   break;
        int mx = 0, bx = 0, by = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int cnt = 0;
                for (int k = 0; k < 8; k++) {
                    int x = i + dx[k], y = j + dy[k];
                    while (x >= 0 && x < n && y >= 0 && y < m) {
                        if (g[x][y] == 'X')
                            cnt++;
                        x += dx[k], y += dy[k];
                    }
                }
                if (g[i][j] == 'X')
                    cnt++;
                if (cnt > mx)
                    mx = cnt, bx = i, by = j;
            }
        }
        for (int k = 0; k < 8; k++) {
            int x = bx + dx[k], y = by + dy[k];
            while (x >= 0 && x < n && y >= 0 && y < m) {
                if (g[x][y] == 'X')
                    g[x][y] = '.';
                x += dx[k], y += dy[k];
            }
        }
        if (g[bx][by] == 'X')
            g[bx][by] = '.';
        ret++;
    }
    return ret;
}
int main() {
    int cases = 0;
    int n, m;
    char g[16][16];
    while (scanf("%d %d", &n, &m) == 2 && n) {
        int cover_col = 0, A[16][16] = {};
        for (int i = 0; i < n; i++)
            scanf("%s", g[i]);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (g[i][j] == 'X') {
                    A[i][j] = ++cover_col;
                }
            }
        }
        dlx.init(cover_col);
   
        int row[2028], rowSize = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                rowSize = 0;
                for (int k = 0; k < 8; k++) {
                    int x = i + dx[k], y = j + dy[k];
                    while (x >= 0 && x < n && y >= 0 && y < m) {
                        if (g[x][y] == 'X')
                            row[rowSize++] = A[x][y];
                        x += dx[k], y += dy[k];
                    }
                }
                if (g[i][j] == 'X')
                    row[rowSize++] = A[i][j];
                sort(row, row + rowSize);
                if (rowSize) {
                    dlx.addrow(rowSize, row, i * m + j);
                }
            }
        }
        dlx.Ans = greedy(n, m, g);
        dlx.DFS(0);
        printf("Case %d: %d\n", ++cases, dlx.Ans);
    }
    return 0;
}