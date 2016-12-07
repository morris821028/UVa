#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
int n, m;
int adj[12];
int next[12];
char way[12], path[12];
int ret = 0;
static inline int max(int x, int y) {
	return x > y ? x : y;
}
void dfs(int pos, int u, int dist, int used_mask) {	
	if (dist >= ret)
		return ;

	if (u == -1) {
		ret = dist;
		memcpy(way, path, n*sizeof(char));
		return ;
	}
	for (int i = u, prev; i != -1; prev = i, i = next[i]) {
		path[pos] = i;
		int c1 = __builtin_popcount(adj[i]&used_mask);
		int c2 = 0;
		for (int j = 0; j < pos; j++) {
			int v = path[j];
			if ((adj[v]>>i)&1) {
				c2 = pos-j + __builtin_popcount(adj[v]&used_mask)-1;
				break;
			}
		}
		int tmp = max(max(c2, c1), dist);
		if (i != u) {
			next[prev] = next[i];
			dfs(pos+1, u, tmp, used_mask^(1<<i));
			next[prev] = i;
		} else {
			dfs(pos+1, next[i], tmp, used_mask^(1<<i));
		}
	}
}
int main() {
	while (scanf("%d %d", &n, &m) == 2)	{
		memset(adj, 0, sizeof(adj));
		for (int i = 0; i < m; i++) {
			int x, y;
			char sx[2], sy[2];
			scanf("%s %s", sx, sy);
			x = sx[0] - 'A', y = sy[0] - 'A';
			adj[x] |= 1<<y;
			adj[y] |= 1<<x;
		}
		
		for (int i = 0; i < n; i++)
			next[i] = i+1;
		next[n-1] = -1;
		ret = n;
		dfs(0, 0, 0, (1<<n)-1);
		printf("%d\n", ret);
		for (int i = 0; i < n; i++)
			printf("%c%c", way[i]+'A', " \n"[i==n-1]);
	}
	return 0;
}

