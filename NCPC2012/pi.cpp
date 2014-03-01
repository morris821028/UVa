#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Maxv 100000
#include <set>
using namespace std;
struct DacingLinks {
    int left, right;
    int up, down;
    int ch, rh;
}DL[1000000];
int s[5001], o[5001], head, size, Ans;
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
int used[5001] = {};
int H() {
    static int c, ret, i, j, time = 0;
    for(c = DL[head].right, ++time, ret = 0; c != head; c = DL[c].right) {
        if(used[c] != time) {
            ret ++, used[c] = time;
            if(ret > Ans)   return ret;
            for(i = DL[c].down; i != c; i = DL[i].down)
                for(j = DL[i].right; j != i; j = DL[j].right)
                    used[DL[j].ch] = time;
        }
    }
    return ret;
}
void DFS(int k) {
    if(k + H() >= Ans)    return;
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
int main() {/*
    freopen("in.txt", "r+t", stdin);
	freopen("out.txt", "w+t", stdout);*/
    int n, A[5005], B[5005];
    while(scanf("%d", &n) == 1 && n) {
        set<int> toy;
        int i;
        for(i = 1; i <= n; i++) {
            scanf("%d %d", &A[i], &B[i]);
            toy.insert(A[i]);
            toy.insert(B[i]);
        }
        init(n);
        int Row[5005], nt;
        for(set<int>::iterator it = toy.begin();
            it != toy.end(); it++) {
            nt = 0;
            for(i = 1; i <= n; i++) {
                if(A[i] == *it || B[i] == *it) {
                    Row[nt++] = i;
                }
            }
            new_row(nt, Row);
        }
        Ans = Maxv;
        DFS(0);
        printf("%d\n", Ans);
    }
    return 0;
}
/*
4
0 1
100 1
100 0
100 200
12
10 20
20 30
30 40
40 50
50 60
60 70
70 80
80 10
10 0
30 0
50 0
70 0
3
1 2
2 3
3 1
0
*/
