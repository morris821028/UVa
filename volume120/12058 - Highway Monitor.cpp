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
    if(k + H() >= Ans)    return;
    if(DL[head].right == head) {
        if(k < Ans) {
        	Ans = k, findflag = 1;
			printf("yes");
			for (int i = 0; i < k; i++)
				printf(" %d", DL[o[i]].data);
			puts("");
        }
        return;
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
        if (findflag)	break;
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
int main() {
	int testcase, cases = 0;
	int n, m, k, x, y;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d", &n, &m, &k);
		vector<int> g[1024];
		for (int i = 1; i <= m; i++) {
			scanf("%d %d", &x, &y);
			g[x].push_back(i);
			g[y].push_back(i);
		}
		assert(m < MAXC);
		init(m);
		int row[1024];
		for (int i = 1; i <= n; i++) {
			sort(g[i].begin(), g[i].end());
			for (int j = 0; j < g[i].size(); j++)
				row[j] = g[i][j];
			addrow(g[i].size(), row, i);
		}
		printf("Case #%d: ", ++cases);
		Ans = k + 1, findflag = 0;
		DFS(0);
		if (Ans == k+1)
			puts("no");
	}
	return 0;
}
