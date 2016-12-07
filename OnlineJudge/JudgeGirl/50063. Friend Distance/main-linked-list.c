#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
int n, m;
char g[16][16], adj[16][16], acnt[16];
char next[16], used[16];
char way[16], path[16];
int ret = 0;
void dfs(int pos, int u, int dist) {	
	if (dist >= ret)
		return ;

	if (u == -1) {
		ret = dist;
		for (int i = 1; i <= n; i++)
			way[i-1] = path[i];
		return ;
	}
	for (int i = u, prev; i != -1; prev = i, i = next[i]) {
		used[i] = pos, path[pos] = i;
		int tmp = dist, cnt = 0;
		for (int j = 0; j < acnt[i]; j++) {
			int v = adj[i][j];
			if (used[v]) {
				if (pos - used[v] > tmp)
					tmp = pos - used[v];
			} else {	
				cnt++;
			}
		}
		tmp = tmp > cnt ? tmp : cnt;
		if (i != u) {
			next[prev] = next[i];
			dfs(pos+1, u, tmp);
			next[prev] = i;
		} else {
			dfs(pos+1, next[i], tmp);
		}
		used[i] = 0;
	}
}
int main() {
	while (scanf("%d %d", &n, &m) == 2)	{
		memset(g, 0, sizeof(g));
		memset(acnt, 0, sizeof(acnt));
		for (int i = 0; i < m; i++) {
			int x, y;
			char sx[2], sy[2];
			scanf("%s %s", sx, sy);
			x = sx[0] - 'A', y = sy[0] - 'A';
			if (g[x][y] == 0) {
				adj[x][acnt[x]++] = y;
				adj[y][acnt[y]++] = x;
				g[x][y] = g[y][x] = 1;
			}
		}
		
		for (int i = 0; i < n; i++)
			next[i] = i+1;
		next[n-1] = -1;
		ret = n;
		dfs(1, 0, 0);
		printf("%d\n", ret);
		for (int i = 0; i < n; i++)
			printf("%c%c", way[i]+'A', " \n"[i==n-1]);
	}
	return 0;
}



