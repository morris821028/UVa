#include <stdio.h>
int n, m, A[20], B[20], ret = 0;
void dfs(int idx, int w, int v) {
	if (w > m)	return ;
	ret = v > ret ? v : ret;
	if (idx == n)	return ;
	dfs(idx+1, w+A[idx], v+B[idx]);
	dfs(idx+1, w, v);
}
int main() {
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; i++)
			scanf("%d %d", &A[i], &B[i]);
		ret = 0;
		dfs(0, 0, 0);
		printf("%d\n", ret);
	}
	return 0;
}
