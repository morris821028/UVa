#include <stdio.h> 

#define MAXN 1024
#define MAXE ((1024*1024)>>5)+1
#define GET(x) (mark[(x)>>5]>>((x)&31)&1)
#define SET(x) (mark[(x)>>5] |= 1<<((x)&31))
int mark[MAXE] = {}, next[MAXN], n, path[MAXN];
int dfs(int u, int dep, int head) {
	if (dep == n)
		return GET(u<<10);
	for (int pre = -1, cur = head; cur >= 0; pre = cur, cur = next[cur]) {
		if (!GET(u<<10|cur))
			continue;
		if (cur != head) {
			next[pre] = next[cur];
			if (dfs(cur, dep+1, head)) {
				path[dep] = cur;
				return 1;
			}
			next[pre] = cur;
		} else {
			if (dfs(cur, dep+1, next[cur])) {
				path[dep] = cur;
				return 1;
			}
		}
	}
	return 0;
}
int main() {
	int m, x, y;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &x, &y);
		SET(x<<10|y), SET(y<<10|x);
	}
	for (int i = 0; i < n; i++)
		next[i] = i+1;
	next[n-1] = -1;
	int ret = dfs(0, 1, 1);
	if (ret) {
		for (int i = 0; i < n; i++)
			printf("%d ", path[i]);
		puts("0");
	} else {
		puts("NO SOLUTION");
	}
	return 0;
}
