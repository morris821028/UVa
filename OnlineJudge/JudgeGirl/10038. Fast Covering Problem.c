#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAXNODE 100000
#define MAXCOL 4096
#define MAXN 5005
struct DacingLinks {
    int left, right, up, down;
    int ch;
} DL[MAXNODE];
int s[MAXCOL], o[MAXCOL], used[MAXCOL] = {};
int head, size, Ans;
void Remove(int c) {
    static int i;
    for (i = DL[c].down; i != c; i = DL[i].down) {
        DL[DL[i].right].left = DL[i].left;
        DL[DL[i].left].right = DL[i].right;
        s[DL[i].ch]--;
    }
}
void Resume(int c) {
    static int i;
    for (i = DL[c].down; i != c; i = DL[i].down) {
        DL[DL[i].right].left = i;
        DL[DL[i].left].right = i;
        s[DL[i].ch]++;
    }
}
int H() {
    static int c, ret, i, j, time = 0;
    for (c = DL[head].right, ++time, ret = 0; c != head; c = DL[c].right) {
        if (used[c] != time) {
        	ret ++, used[c] = time;
            for (i = DL[c].down; i != c; i = DL[i].down)
                for (j = DL[i].right; j != i; j = DL[j].right)
                	used[DL[j].ch] = time;
        }
    }
    return ret;
}
void DFS(int k) {
    if (k + H() >= Ans)
		return;
    if (DL[head].right == head) {
        if (k < Ans)    Ans = k;
        return;
    }
    int t = INT_MAX, c, i, j;
    for (i = DL[head].right; i != head; i = DL[i].right) {
        if (s[i] < t) 
            t = s[i], c = i;
    }
    for (i = DL[c].down; i != c; i = DL[i].down) {
        Remove(i);
        for (j = DL[i].right; j != i; j = DL[j].right)
			Remove(j);
        DFS(k+1);
        for (j = DL[i].left; j != i; j = DL[j].left)        
			Resume(j);
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
    int i, r, row = -1, k;
    for (i = 0; i < n; i++) {
        r = Row[i];
        DL[size].ch = r, s[r]++;
        if (row == -1) {
            row = new_node(DL[DL[r].ch].up, DL[r].ch, size, size);
        } else {
            k = new_node(DL[DL[r].ch].up, DL[r].ch, DL[row].left, row);
        }
    }
}
void init(int m) {
    size = 0;
    head = new_node(0, 0, 0, 0);
    int i;
    for (i = 1; i <= m; i++) {
        new_node(i, i, DL[head].left, head);
        DL[i].ch = i, s[i] = 0;
    }
}
int main() {
    int n, A[MAXN], B[MAXN];
    while (scanf("%d", &n) == 1 && n) {
		int toy[10005] = {}, R[MAXCOL];
		for (int i = 1; i <= n; i++) {
		    scanf("%d %d", &A[i], &B[i]);
		    toy[A[i]] = toy[A[i]] = 1;
		}
		
		init(n);
		for (int i = 0; i <= 10000; i++) {
			int nt = 0;
			for (int j = 1; j <= n; j++) {
				if (A[j] == i || B[j] == i)
					R[nt++] = j;
			}
			new_row(nt, R);
		}
		Ans = MAXN;
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



