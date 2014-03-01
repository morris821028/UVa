#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Maxv 100000
using namespace std;
struct DacingLinks {
    int left, right;
    int up, down;
    int data, ch, rh;
}DL[5000];
int s[40], o[40], head, size, Ans;
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
int used[40] = {};
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
    if(k + H()*2 >= Ans)    return; // H()*? guess.
    if(DL[head].right == head) {
        if(k < Ans)    Ans = k;
        return;
    }
    int t = Maxv, c, i, j;
    for(i = DL[head].right; i != head; i = DL[i].right) {
        if(s[i] < t) {
            t = s[i], c = i;
        }
    }
    for(i = DL[c].down; i != c; i = DL[i].down) {
        Remove(i);
        for(j = DL[i].right; j != i; j = DL[j].right)    Remove(j);
        DFS(k+1);
        for(j = DL[i].left; j != i; j = DL[j].left)        Resume(j);
        Resume(i);
    }
}
int new_node(int up, int down, int left, int right) {
    DL[size].up = up, DL[size].down = down;
    DL[size].left = left, DL[size].right = right;
    DL[up].down = DL[down].up = DL[left].right = DL[right].left = size;
    return size++;
}
void new_row(int n, int Row[]) {
    int a, r, row = -1, k;
    for(a = 0; a < n; a++) {
        r = Row[a];
        DL[size].ch = r, s[r]++;
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
int main() {
    int n, m;
    /*freopen("in.txt", "r+t", stdin);
	freopen("out2.txt", "w+t", stdout);*/
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0 && m == 0)
            break;
        int i, j;
        int g[40][40] = {}, x, y;
        for(i = 1; i <= m; i++) {
            scanf("%d %d", &x, &y);
            g[x][y] = 1;
            g[y][x] = 1;
        }
        init(n);
        int row[500], nt;
        for(i = 1; i <= n; i++) {
            nt = 0;
            for(j = 1; j <= n; j++) {
                if(j == i || g[i][j])
                    row[nt++] = j;
            }
            new_row(nt, row);
        }
        Ans = Maxv;
        DFS(0);
        printf("%d\n", Ans);
    }
    return 0;
}
