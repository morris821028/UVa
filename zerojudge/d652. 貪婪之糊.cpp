#include<stdio.h>
main() {
	int n, A[50];
	while(scanf("%d", &n) == 1) {
		int DP[51][51] = {}, a, b, c, d;
		for(a = 0; a < n; a++)
			scanf("%d", &A[a]);
		for(a = 1, n--; a < n; a++) {
			for(b= 0, c= a + b; c < n; b++, c++) {
				int min = 2147483647, t;
				for(d = b; d < c; d++) {
					t = DP[b][d] + DP[d+1][c] + A[b]*A[d+1]*A[c+1];
					min = (min < t) ? min : t;
				}
				DP[b][c] = min;
			}
		}
		printf("%d\n", DP[0][n-1]);
	}
	return 0;
}
