#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define MAXN 64
int64_t e[MAXN];
int32_t D[MAXN], ret;
static inline int log2int(int64_t x) {
	return 63 - __builtin_clzll(x); 
}
int H(int64_t visited) {
	int t = 0;
	for (int i = 0; (1LL<<i) <= visited; i++) {
		if ((visited>>i)&1)
			t += D[i];
	}
	return t;
}
void dfs(int64_t visited, int32_t w) {
	if (visited == 0) {
		if (w > ret)
			ret = w;
		return ;
	}
	if (w + H(visited) <= ret)
		return ;
	int idx = log2int(visited&(-visited));
	dfs((visited^(1LL<<idx))&e[idx], w + D[idx]);
	dfs(visited^(1LL<<idx), w);
}
int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++)
			scanf("%d", &D[i]);
		for (int i = 0; i < n; i++) {
			int64_t mask = 0;
			for (int j = 0, x; j < n; j++) {
				scanf("%d", &x);
				mask |= (int64_t) x << j;
			}
			e[i] = ~mask;
		}
		ret = 0;
		dfs((1LL<<n)-1, 0);
		printf("%d\n", ret);
	}
	return 0;
}


