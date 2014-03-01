#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Maxv 100000
#include <vector>
using namespace std;
struct DacingLinks {
    int left, right;
    int up, down;
    int ch;
}DL[3000000];
int s[1005001], o[1005001], head, size, Ans;
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
int used[1005001] = {};
int H() {
    static int c, ret, i, j, time = 0;
    for(c = DL[head].right, ++time, ret = 0; c != head; c = DL[c].right) {
        if(used[c] != time) {
            ret ++, used[c] = time;
            if(ret > 8)    return ret;
            for(i = DL[c].down; i != c; i = DL[i].down)
                for(j = DL[i].right; j != i; j = DL[j].right)
                    used[DL[j].ch] = time;
        }
    }
    return ret;
}
void DFS(int k) {
    if(k + H() > 8 || Ans <= 8)    return;
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
        }else {
            k = new_node(DL[DL[r].ch].up, DL[r].ch, DL[row].left, row);
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
struct Pt {
    int x, e;
};
int main() {
    int n, m, x, y, i;
    while(scanf("%d %d", &n, &m) == 2 && n) {
        vector<Pt> g[n+1];
        Pt tmp;
        for(i = 0; i < m; i++) {
            scanf("%d %d", &x, &y);
            x++, y++;
            tmp.x = y, tmp.e = i+n+1;
            g[x].push_back(tmp);
            tmp.x = x;
            g[y].push_back(tmp);
        }
        init(n+m);
        int Row[10005], nt;
        for(i = 1; i <= n; i++) {
            used[i] = 0;
            nt = 1, Row[0] = i;
            for(vector<Pt>::iterator it = g[i].begin();
                it != g[i].end(); it++)
                Row[nt++] = it->x, Row[nt++] = it->e;
            new_row(nt, Row);
        }
        Ans = Maxv;
        DFS(0);
        if(Ans <= 8)
            puts("Nice boat.");
        else
            puts("Makoto should die!");
    }
    return 0;
}
