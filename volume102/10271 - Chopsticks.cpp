#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define oo 100000000
int DP[1010][5001];
int L[5001], bad[5001];
int cmp(const void *i, const void *j) {
	return *(int *)j - *(int *)i;
}
int min(int x, int y) {
	return x < y ? x : y;
}
int findDP(int k, int n) {
	if(DP[k][n] != -1)
		return DP[k][n];
	if(n < 3*k) {
		DP[k][n] = oo;
	} else if(k == 0) {
		DP[k][n] = 0;
	} else {
		DP[k][n] = min(findDP(k, n-1), findDP(k-1, n-2)+bad[n]);
	}
	return DP[k][n];
}
int main() {
	int t, n, k, i, j;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &k, &n);
		for(i = 1; i <= n; i++)
			scanf("%d", &L[i]);
		k += 8;
		qsort(L+1, n, sizeof(int), cmp);
		for(i = 2; i <= n; i++)
			bad[i] = (L[i]-L[i-1])*(L[i]-L[i-1]);
		for(i = 0; i <= k; i++)
			for(j = 0; j <= n; j++)
				DP[i][j] = -1;
		printf("%d\n", findDP(k, n));
	}
    return 0;
}
