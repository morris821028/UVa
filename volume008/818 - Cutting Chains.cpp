#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;

int g[16][16], gmask[16];
int visited[16];
int dfs(int u, int p, int open, int n) {
	visited[u] = 1;
	for (int i = 0; i < n; i++) {
		if ((open>>i)&1)
			continue;
		if (g[u][i] == 0 || i == p)
			continue;
		if (visited[i] || dfs(i, u, open, n))
			return 1;
	}
	return 0;
}
int checkChain(int open, int n) {
	for (int i = 0; i < n; i++) {
		if ((open>>i)&1)
			continue;
		int t = gmask[i]^(gmask[i]&open);
		int degree = __builtin_popcount(t);
		if (degree > 2)
			return 0;
	}
	
	int op = __builtin_popcount(open);
	int comp = 0;
	memset(visited, 0, sizeof(visited));
	for (int i = 0; i < n; i++) {
		if ((open>>i)&1)	continue;
		if (visited[i] == 0) {
			if (dfs(i, -1, open, n)) // have cycle
				return 0;
			comp++;
		}
	}
	return op >= comp - 1;
}
int main() {
	int cases = 0;
	int n, x, y;
	while (scanf("%d", &n) == 1 && n) {
		memset(g, 0, sizeof(g));
		memset(gmask, 0, sizeof(gmask));
		while (scanf("%d %d", &x, &y) == 2) {
			if (x == -1)	break;
			x--, y--;
			g[x][y] = g[y][x] = 1;
			gmask[x] |= 1<<y, gmask[y] |= 1<<x;
		}
		
		int ret = 0x3f3f3f3f;
		for (int i = 0; i < (1<<n); i++) { // 1: open.
			int op = __builtin_popcount(i);
			if (op >= ret)	continue;
			if (checkChain(i, n))
				ret = min(ret, op); 
		}
		printf("Set %d: Minimum links to open is %d\n", ++cases, ret);
	}
	return 0;
}
