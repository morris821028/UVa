#include <stdio.h>
#include <algorithm>
using namespace std;
struct DancingLinks {
    int left, right, up, down, ch;
    int rh; // 額外的 data
} DL[100000 + 1001];
int s[1001], o[1001], head, size;
int n; // this problem need n for output process.
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
int found;
int data[1000][100];
void print(int k) {
    int i, j;
    int g[4][4];
    int r[105], rn;
    for(i = 0; i < k; i++) {
        rn = 0;
        for(j = 0; data[DL[o[i]].rh][j] > 0; j++)
            r[rn++] = data[DL[o[i]].rh][j];
        for(j = 1; j < rn; j++)
            g[(r[j]-n-1)/4][(r[j]-n-1)%4] = r[0];
    }
    for(i = 0; i < 4; i++, puts(""))
        for(j = 0; j < 4; j++)
            printf("%d", g[i][j]);
}
void dfs(int dep) {
    if(found)   return;
    if(DL[head].right == head) {
        found = 1;
        print(dep);
        return;
    }
    int tmp = 0xffff, c, i, j;
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
    return size++;
}
void newrow(int r[], int rn, int rh) {
    int i, j, h;
    for(i = 0; i < rn; i++) {
        DL[size].ch = r[i], s[r[i]]++;
        DL[size].rh = rh; // 額外的 data
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
int main() {
    int i, j, k, x, y, a, b;
    char g[20][20];
    int first = 0;
    while(scanf("%d", &n) == 1 && n) {
        if(first)   puts("");
        first = 1;
        int column = n+16, r[500], row = 0;
        init(column);
        for(i = 0; i < n; i++) {
            scanf("%d %d", &x, &y);
            for(j = 0; j < x; j++)
                scanf("%s", g[j]);
            for(j = 0; j+x <= 4; j++) {
                for(k = 0; k+y <= 4; k++) {
                    int rn = 0;
                    r[rn++] = i+1;
                    for(a = 0; a < x; a++)
                    for(b = 0; b < y; b++)
                        if(g[a][b] == '1') {
                        r[rn++] = (j+a)*4 + k+b + n + 1;
                    }
                    newrow(r, rn, row);
                    for(a = 0; a < rn; a++)
                        data[row][a] = r[a];
                    data[row][rn] = -1;
                    row++;
                }
            }
        }
        found = 0;
        dfs(0);
        if(!found)
            puts("No solution possible");
    }
    return 0;
}
