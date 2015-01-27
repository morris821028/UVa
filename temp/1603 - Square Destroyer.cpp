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
#define MAXR 1024
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

int main() {
    int testcase;
    int n, m, x;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        assert(n * n < MAXC);
        int label = 0, hLabel[16][16], vLabel[16][16];
        int enable[2048], cover_col = 0;
        vector<int> g[2048];
        for (int i = 1; i <= n + 1; i++) {
            for (int j = 1; j <= n; j++)
                hLabel[i][j] = ++label, enable[label] = 1;
            for (int j = 1; j <= n + 1; j++)
                vLabel[i][j] = ++label, enable[label] = 1;
        }
        for (int k = 0; k <= n; k++) {
            for (int i = 1; i+k <= n; i++) {
                for (int j = 1; j+k <= n; j++) {
                    cover_col++;
                    for (int l = 0; l <= k; l++) {
                        g[hLabel[i][j+l]].push_back(cover_col);
                        g[hLabel[i+1+k][j+l]].push_back(cover_col);
                        g[vLabel[i+l][j]].push_back(cover_col);
                        g[vLabel[i+l][j+1+k]].push_back(cover_col);
//                        printf("%d %d %d %d\n", hLabel[i][j+l], hLabel[i+1+k][j+l],
//                                    vLabel[i+l][j], vLabel[i+l][j+1+k]);
                    }
//                    puts("--");
                }
            }
        }
        dlx.init(cover_col);
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%d", &x);
            enable[x] = 0;
        }
        int cover[2048] = {}, preCover = 0;
        int row[2028], rowSize = 0;
        for (int i = 1; i <= label; i++) {
            if (!enable[i] || g[i].size() == 0) {
                for (int j = 0; j < g[i].size(); j++)
                    cover[g[i][j]] = 1;
                continue;
            }
            rowSize = 0;
            for (int j = 0; j < g[i].size(); j++)
                row[rowSize++] = g[i][j];
            dlx.addrow(rowSize, row, i);
        }
        rowSize = 0;
        for (int i = 1; i <= cover_col; i++) {
            if (cover[i])
                row[rowSize++] = i, preCover = 1;
        }
        if (preCover)
            dlx.addrow(rowSize, row, label + 1);
        dlx.Ans = 0x3f3f3f3f;
        dlx.DFS(0);
        printf("%d\n", dlx.Ans - preCover);
    }
    return 0;
}