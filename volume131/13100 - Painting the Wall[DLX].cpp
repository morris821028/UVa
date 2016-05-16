// TLE
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
#define MAXR 800*800
struct DacingLinks {
    int left, right;
    int up, down;
    int ch, rh;
    int data; // extra info
} DL[MAXE];
int s[MAXC], o[MAXR], head, size, Ans;
int sol[MAXR];
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
    if(k + H() >= Ans)    return;
    if(DL[head].right == head) {
    	if (k < Ans) {
			Ans = k;
			for (int i = 0; i < k; i++)
				sol[i] = DL[o[i]].data;
		}
        return ;
    }
    int t = MAXV, c, i, j;
    for(i = DL[head].right; i != head; i = DL[i].right) {
        if(s[i] < t) {
            t = s[i], c = i;
        }
    }
    for(i = DL[c].down; i != c; i = DL[i].down) {
        o[k] = i;
        Remove(i);
        for(j = DL[i].right; j != i; j = DL[j].right)	Remove(j);
        DFS(k+1);
        for(j = DL[i].left; j != i; j = DL[j].left)     Resume(j);
        Resume(i);
    }
}
int new_node(int up, int down, int left, int right) {
    assert(size < MAXE);
    DL[size].up = up, DL[size].down = down;
    DL[size].left = left, DL[size].right = right;
    DL[up].down = DL[down].up = DL[left].right = DL[right].left = size;
    assert(size < MAXE);
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
char g[1024][1024];
int ig[1024][1024];
int C[800*800][4];
int main() {
    int n, m;
    while (scanf("%d %d", &n, &m) == 2) {
        for (int i = 1; i <= n; i++)
        	scanf("%s", g[i]+1);
        int size = 0;
        for (int i = 1; i <= n; i++) {
        	for (int j = 1; j <= m; j++) {
        		if (g[i][j] == '*')
        			ig[i][j] = ++size;
			}
		}
        init(size);
        
        static int row[800*800];
        int id = 0;
        for (int i = 1; i <= n; i++) {
        	for (int j = 1; j <= m; j++) {
        		if (g[i][j] != '*')
        			continue;
        		if (i == 1 || g[i-1][j] == '.') {
        			int k = i, sz = 0;
        			while (k <= n && g[k][j] == '*')
        				row[sz] = ig[k][j], k++, sz++;
        			C[id][0] = 0, C[id][1] = j;
        			C[id][2] = i, C[id][3] = k-1;
        			addrow(sz, row, id), id++;
				}
				if (j == 1 || g[i][j-1] == '.') {
					int k = j, sz = 0;
        			while (k <= m && g[i][k] == '*')
        				row[sz] = ig[i][k], k++, sz++;
        			C[id][0] = 1, C[id][1] = i;
        			C[id][2] = j, C[id][3] = k-1;
        			addrow(sz, row, id), id++;
				}
				assert(id < MAXR);
			}
		}
        Ans = n*m;
        DFS(0);
        printf("%d\n", Ans);
        for (int i = 0; i < Ans; i++) {
        	int id = sol[i];
        	printf("%s %d %d %d\n", C[id][0] == 0 ? "vline" : "hline", C[id][1], C[id][2], C[id][3]);
		}
    }
    return 0;
}
