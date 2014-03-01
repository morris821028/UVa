#include<stdio.h>
int DP[11][11] = {}, a, b, c, d;
int Wy[11][11] = {};
void Backtracking(int l, int r) {
	if(l+1 < r) {
		int m = Wy[l][r];
		printf("(");
		Backtracking(l, m);
		printf(" x ");
		Backtracking(m+1, r);
		printf(")");
	}
	if(l == r)
		printf("A%d", l+1);
	if(l+1 == r)
		printf("(A%d x A%d)", l+1, r+1);
}
main() {
	int n, A[11], C = 0;
	while(scanf("%d", &n) == 1 && n) {

		for(a = 0; a < n; a++)
			scanf("%d %d", &A[a], &A[a+1]);
		for(a = 1; a < n; a++) {
			for(b= 0, c= a + b; c < n; b++, c++) {
				int min = 2147483647, t, set;
				for(d = b; d < c; d++) {
					t = DP[b][d] + DP[d+1][c] + A[b]*A[d+1]*A[c+1];
					if(min > t) {
						min = t, set = d;
					}
				}
				DP[b][c] = min, Wy[b][c] = set;
			}
		}
		printf("Case %d: ", ++C);
		Backtracking(0, n-1);
		puts("");
	}
	return 0;
}
