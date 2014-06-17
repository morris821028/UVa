#include<stdio.h>
typedef struct {
	int t[50][50];
}Matrix;
Matrix A, In, init;
Matrix mult(Matrix x, Matrix  y, int n) {
	Matrix t = init;
	int i, j, k;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			for(k = 0; k < n; k++) {
				t.t[i][k] += x.t[i][j]*y.t[j][k];
			}
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			t.t[i][j] %= 5281;
	return t;
}
int ans(int k, int n) {
	Matrix x = In, y = A;
	while(k) {
		if(k&1) x = mult(x, y, n);
		y = mult(y, y, n);
		k /= 2;
	}
	int Q, i, j;
	scanf("%d", &Q);
	while(Q--) {
		scanf("%d %d", &i, &j);
		printf("%d\n", x.t[i-1][j-1]);
	}
}
main() {
	int n, a, b, k, x, y, s;
	while(scanf("%d %d", &n, &k) == 2) {	
		for(a = 0; a < n; a++)
			for(b = 0; b < n; b++)
				A.t[a][b] = 0, In.t[a][b] = 0,
				init.t[a][b] = 0;
		for(a = 0; a < n; a++) In.t[a][a] = 1;
		while(scanf("%d %d %d", &x, &y, &s) == 3) {
			if(x + y + s == 0) break;
			A.t[x-1][y-1] += s;
		}
		ans(k, n);
	}
	return 0;
}
