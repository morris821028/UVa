#include <bits/stdc++.h> 
using namespace std;
const int MAXN = 1024;
static int A[MAXN][MAXN];
/*
integer frieze pattern: http://www.washingtonart.net/whealton/fpoi.html
*/
int main() {
	int n, x, y;
	while (scanf("%d", &n) == 1 && n) {
		scanf("%d %d", &x, &y);
		for (int i = 0; i < n; i++)
			scanf("%d", &A[0][i]);

		for (int i = 1; i <= n; i++) {
			A[i][0] = A[i][n-1] = 1;
			for (int j = 1; j < n-1; j++)
				A[i][j] = (A[i-1][j+1]*A[i][j-1]+1)/A[i-1][j];
		}
		printf("%d\n", A[(y-1)%(n+1)][x-1]);
	}
	return 0;
}
/*
4
2 3
1 2 1 1
6
5 9
1 1 1 1 2 1
*/
