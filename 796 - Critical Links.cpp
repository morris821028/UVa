#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define oo 1000
int link[100][100], n;
int depth[100];
int used[100];
int cutBridge[100][100];
int DFS(int node, int d, int p) {
	int i, back = oo, tmp;
	depth[node] = d;
	for(i = 0; i < n; i++) {
		if(link[node][i] == 1) {
			if(used[i] == 0) {
				used[i] = 1;
				tmp = DFS(i, d+1, node);
				if(tmp > d) {
					cutBridge[node][i] = 1;
					cutBridge[i][node] = 1;
				}
				back = min(back, tmp);
			} else {
				if(i != p)
                    back = min(back, depth[i]);
			}
		}
	}
	return back;
}
int main() {
	int x, y, m, i ,j, Case = 0;
	while(scanf("%d", &n) == 1) {
		memset(link, 0, sizeof(link));
		memset(depth, 0, sizeof(depth));
		memset(used, 0, sizeof(used));
		memset(cutBridge, 0, sizeof(cutBridge));
		for(i = 0; i < n; i++) {
			scanf("%d ", &x);
			scanf("(%d)", &m);
			while(m--) {
				scanf("%d", &y);
				link[x][y] = 1;
				link[y][x] = 1;
			}
		}
		for(i = 0; i < n; i++) {
			if(used[i] == 0) {
				used[i] = 1;
				DFS(i, 1, -1);
			}
		}
		int ans = 0;
		for(i = 0; i < n; i++) {
			for(j = i+1; j < n; j++) {
				if(cutBridge[i][j] != 0)
					ans++;
			}
		}
		printf("%d critical links\n", ans);
		for(i = 0; i < n; i++) {
			for(j = i+1; j < n; j++)
				if(cutBridge[i][j] != 0)
					printf("%d - %d\n", i, j);
		}
		puts("");
	}
    return 0;
}
