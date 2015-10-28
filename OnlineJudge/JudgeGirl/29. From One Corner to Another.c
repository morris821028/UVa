#include <stdio.h>

int dfs(int n, int m) {
	if (n < 0 || m < 0)
		return 0;
	if (n == 0 && m == 0)
		return 1;
	return dfs(n-1, m) + dfs(n, m-1);
}
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2)
		printf("%d\n", dfs(n-1, m-1));
	return 0;
}
