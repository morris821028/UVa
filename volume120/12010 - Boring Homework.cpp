#include <stdio.h>
#include <string.h>
struct Node {
	int v, l, r, porder;
};
Node BST[128];
char g[256][128];
int porder = 0, mxdep;
void build(int nd, int dep) {
	if(dep > mxdep)	mxdep = dep;
	if(BST[nd].l != -1)
		build(BST[nd].l, dep+2);
	BST[nd].porder = porder++;	
	if(BST[nd].r != -1)
		build(BST[nd].r, dep+2);
		
	if(BST[nd].l != -1) {
		g[dep][BST[BST[nd].l].porder] = '+';
		g[dep+1][BST[BST[nd].l].porder] = '|';
		for(int i = BST[BST[nd].l].porder + 1; i < BST[nd].porder; i++)
			g[dep][i] = '-';
	}
	g[dep][BST[nd].porder] = 'o';
	if(BST[nd].r != -1) {
		for(int i = BST[BST[nd].r].porder - 1; i > BST[nd].porder; i--)
			g[dep][i] = '-';
		g[dep][BST[BST[nd].r].porder] = '+';
		g[dep+1][BST[BST[nd].r].porder] = '|';
	}
}
int main() {
	int testcase, cases = 0, N;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &N);
		memset(BST, -1, sizeof(BST));
		scanf("%d", &BST[0].v);
		int size = 1, x;
		for(int i = 1; i < N; i++) {
			scanf("%d", &x);
			int idx = 0;
			do {
				if(x < BST[idx].v) {
					if(BST[idx].l != -1)
						idx = BST[idx].l;
					else
						BST[idx].l = size, BST[size++].v = x, idx = 0;
				} else {
					if(BST[idx].r != -1)
						idx = BST[idx].r;
					else
						BST[idx].r = size, BST[size++].v = x, idx = 0;
				}
			} while(idx);
		}
		porder = 0, mxdep = 0;
		memset(g, ' ', sizeof(g));
		build(0, 0);
		printf("Case #%d:\n", ++cases);
		for(int i = 0; i <= mxdep; i++) {
			for(int j = N; g[i][j] == ' '; j--)
				g[i][j] = '\0';
			printf("%s\n", g[i]);
		}
	}
	return 0;
}
/*
3
3 3 1 2
6 4 5 6 1 3 2
5 3 4 5 2 1

Case #1:
+-o
|
o+
 |
 o
Case #2:
+--o+
|   |
o-+ o+
  |  |
 +o  o
 |
 o
Case #3:
 +o+
 | |
+o o+
|   |
o   o
*/
