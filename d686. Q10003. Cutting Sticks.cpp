#include<stdio.h>		
main() {
	int n, L, A[52] = {0};
	while(scanf("%d", &L) == 1 && L) {
		scanf("%d", &n);
		int DP[52][52] = {}, a, b, c, d;
		for(a = 1; a <= n; a++)
			scanf("%d", &A[a]);
		A[++n] = L;
		for(a = 2; a <= n; a++) {
			for(b= 0, c= a+b; c <= n; b++, c++) {
				int min = 2147483647, t;
				for(d = b+1; d < c; d++) {
					t = DP[b][d] + DP[d][c] + A[c] - A[b];
					if(min > t)	min = t;
				}
				DP[b][c] = min;
			}
		}
		printf("The minimum cutting is %d.\n", DP[0][n]);
	}
	return 0;
}
