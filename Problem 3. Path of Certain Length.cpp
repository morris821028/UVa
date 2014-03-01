#include<stdio.h>
typedef struct Matrix{
	int t[15][15];
};
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
			t.t[i][k] =	(t.t[i][k] != 0);
	return t;
}
int ans(int k, int i, int j, int n) {
	Matrix x = In, y = A;
	while(k) {
		if(k&1) x = mult(x, y, n);
		y = mult(y, y, n);
		k /= 2;
	}
	return x.t[i-1][j-1];
}
main() {
    int T, n, m, x, y, a, b;
    scanf("%d", &T);
    while(T--) {
        scanf("%d %d", &n, &m);
		for(a = 0; a < n; a++)
		    for(b = 0; b < n; b++)
				A.t[a][b] = 0, In.t[a][b] = 0,
				init.t[a][b] = 0;
		for(a = 0; a < n; a++) In.t[a][a] = 1;
		for(a = 0; a < n; a++)
			for(b = 0; b < n; b++)
				scanf("%d", &A.t[a][b]);
		scanf("%d %d", &x, &y);
		puts((ans(m, x, y, n)) ? "Yes" : "No");
    }
    return 0;
}
