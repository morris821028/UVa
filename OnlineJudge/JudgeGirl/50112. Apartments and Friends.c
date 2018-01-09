#include <stdio.h>
#include <stdlib.h>
#define MAXN 16
int n, next[MAXN], ret, pos[MAXN];
int g[MAXN];
void dfs(int dep, int head, int cost, int h, int p) {
	if (cost+h+p >= ret)
		return ;
	if (head == -1) {
		ret = cost;
		return ;
	}
	for (int pre = -1, cur = head; cur >= 0; pre = cur, cur = next[cur]) {
		int cc = cost, pp = p, hh = h+p;
		pos[cur] = dep;
		for (int i = 0; i < n; i++) {
			if (!((g[cur]>>i)&1)) 
				continue;
			if (pos[i] >= 0)
				cc += dep-pos[i], hh -= dep-pos[i], pp--;
			else
				pp++;
		}
		if (cur != head) {
			next[pre] = next[cur];
			dfs(dep+1, head, cc, hh, pp);
			next[pre] = cur;
		} else {
			dfs(dep+1, next[cur], cc, hh, pp);
		}
		pos[cur] = -1;
	}
}
int main() {
	int m, x, y;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &x, &y);
		g[x] |= 1<<y, g[y] |= 1<<x;
	}
	for (int i = 0; i < n; i++)
		next[i] = i+1, pos[i] = -1;
	next[n-1] = -1;
	ret = 0x3f3f3f3f;
	dfs(0, 0, 0, 0, 0);
	printf("%d\n", ret);
	return 0;
}
