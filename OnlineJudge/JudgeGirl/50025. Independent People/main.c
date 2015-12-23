#include <stdio.h>

#define MAXN 128
int n, m, g[MAXN][MAXN], ret, sol[MAXN];
int findIndepSet(int n, int A[], int sz) {
	if (sz == m) {
		for (int i = 0; i < sz; i++)
			printf("%d%c", sol[i], i != sz-1 ? ' ' : '\n');
		return 1;
	}
	if (sz + n < m)
		return 0;
	if (n == 0)
		return 0;
	int next[MAXN], tn = 0;
	for (int i = 1; i < n; i++) {
		if (g[A[i]][A[0]] == 0)
			next[tn++] = A[i];
	}
	sol[sz] = A[0];
	return findIndepSet(tn, next, sz+1) || findIndepSet(n-1, A+1, sz);
}
int main() {
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				scanf("%d", &g[i][j]);
		}
		int A[MAXN];
		for (int i = 0; i < n; i++)
			A[i] = i;
		int f = findIndepSet(n, A, 0);
		if (!f)
			printf("no solution\n");
	}
	return 0;
}
