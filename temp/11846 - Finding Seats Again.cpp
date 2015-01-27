#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <assert.h>
using namespace std;

char g[32][32];
int ig[32][32], N, K, ret[32];

class DLX {
public:
    struct DancingLinks {
        int left, right, up, down, ch;
        int id, lx, ly, rx, ry; // extra data
    } DL[131072 + 256];
    int s[512], o[512], head, size;
    void remove(int c) {
        DL[DL[c].right].left = DL[c].left;
        DL[DL[c].left].right = DL[c].right;
        int i, j;
        for(i = DL[c].down; i != c; i = DL[i].down) {
            for(j = DL[i].right; j != i; j = DL[j].right) {
                DL[DL[j].down].up = DL[j].up;
                DL[DL[j].up].down = DL[j].down;
                s[DL[j].ch]--;
            }
        }
    }
    void resume(int c) {
        int i, j;
        for(i = DL[c].down; i != c; i = DL[i].down) {
            for(j = DL[i].left; j != i; j = DL[j].left) {
                DL[DL[j].down].up = j;
                DL[DL[j].up].down = j;
                s[DL[j].ch]++;
            }
        }
        DL[DL[c].right].left = c;
        DL[DL[c].left].right = c;
    }
    void print(int dep) {
        char g[32][32];
        for (int i = 0; i < dep; i++) {
            for (int x = DL[o[i]].lx; x <= DL[o[i]].rx; x++) {
                for (int y = DL[o[i]].ly; y <= DL[o[i]].ry; y++) {
                    g[x][y] = DL[o[i]].id - 1 + 'A';
                }
            }
        }
        for (int i = 0; i < N; i++, puts("")) {
            for (int j = 0; j < N; j++) {
                putchar(g[i][j]);
            }
        }
    }
    int found;
    void dfs(int dep) {
        if (found) return;
        if (DL[head].right == head) {
            found++;
            print(dep);
            return;
        }
        int tmp = 0x3f3f3f3f, c = 0, i, j;
        for(i = DL[head].right; i != head; i = DL[i].right)
            if(s[i] < tmp)
                tmp = s[i], c = i;
        remove(c);
        for(i = DL[c].down; i != c; i = DL[i].down) {
            o[dep] = i;
            for(j = DL[i].right; j != i; j = DL[j].right)
                remove(DL[j].ch);
            dfs(dep+1);
            for(j = DL[i].left; j != i; j = DL[j].left)
                resume(DL[j].ch);
        }
        resume(c);
    }
    int getnode(int u, int d, int l, int r) {
        DL[size].up = u, DL[size].down = d;
        DL[size].left = l, DL[size].right = r;
        DL[u].down = DL[d].up = DL[l].right = DL[r].left = size;
        assert(size < 131072);
        return size++;
    }
    void newrow(int r[], int rn, int id, int lx, int ly, int rx, int ry) {
        int i, j, h = 0;
        for(i = 0; i < rn; i++) {
            DL[size].ch = r[i], s[r[i]]++;
            DL[size].id = id; // extra data
            DL[size].lx = lx; // extra data
            DL[size].ly = ly; // extra data
            DL[size].rx = rx; // extra data
            DL[size].ry = ry; // extra data
            if(i) {
                j = getnode(DL[DL[r[i]].ch].up, DL[r[i]].ch, DL[h].left, h);
            } else {
                h = getnode(DL[DL[r[i]].ch].up, DL[r[i]].ch, size, size);
            }
        }
    }
    void init(int c) {// total column
        size = 0;
        head = getnode(0,0,0,0);
        int i;
        for(i = 1; i <= c; i++) {
            getnode(i, i, DL[head].left, head);
            DL[i].ch = i, s[i] = 0;
        }
    }
} DLX;

int canPlace(int lx, int ly, int rx, int ry, int &id) {
    int cnt = 0, size = 0;
    for (int i = lx; i <= rx; i++) {
        for (int j = ly; j <= ry; j++) {
            if (ig[i][j]) {
                id = ig[i][j], size = g[i][j] - '0';
                cnt++;
                if (cnt > 1 || (rx - lx + 1) * (ry - ly + 1) != size)
                    return 0;
            }
        }
    }
    return cnt == 1 && (rx - lx + 1) * (ry - ly + 1) == size;
}
void place(int lx, int ly, int rx, int ry, int id) {
    static int row[512], rowSize;
    rowSize = 0;
    for (int i = lx; i <= rx; i++) {
        for (int j = ly; j <= ry; j++) {
            row[rowSize++] = i * N + j + 1;
        }
    }
    row[rowSize++] = N * N + id;
    DLX.newrow(row, rowSize, id, lx, ly, rx, ry);
}
int main() {
    while (scanf("%d %d", &N, &K) == 2 && N) {
        for (int i = 0; i < N; i++)
            scanf("%s", g[i]);
        memset(ig, 0, sizeof(ig));
        int label = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (g[i][j] >= '0' && g[i][j] <= '9') {
                    ig[i][j] = ++label;
                }
            }
        }
        
        DLX.init(N * N + label);
        
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int p = i; p < N; p++) {
                    for (int q = j; q < N; q++) {
                        int id;
                        if (canPlace(i, j, p, q, id))
                            place(i, j, p, q, id);
                    }
                }
            }
        }
        
        DLX.found = 0;
        DLX.dfs(0);
    }
    return 0;
}
