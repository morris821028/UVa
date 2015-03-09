#include<stdio.h>
#define Max 1000
typedef struct {
	int t[10][10];
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
int Floyd_Warshall(int n) {
	int a, b, c;
	for(a = 0; a < n; a++)
		for(b = 0; b < n; b++)
			if(A.t[a][b] == 0)
				A.t[a][b] = Max;
	for(a = 0; a < n; a++)
		for(b = 0; b < n; b++)
			for(c = 0; c < n; c++)
				if(A.t[b][a] + A.t[a][c] < A.t[b][c])
					A.t[b][c] = A.t[b][a] + A.t[a][c];
	int tx = -1, ty = -1, flag = 1;
	for(a = 0; a < n && flag == 1; a++)
		for(b = 0; b < n && flag == 1; b++)
			if(A.t[a][b] == Max) {
				tx = a, ty = b;
				flag = 0;
			}
	printf("%d\n%d\n", tx+1, ty+1);
}
main() {
	int n, a, b, i, j, k;
	char s[11];
	while(scanf("%d", &n) == 1) {	
		for(a = 0; a < n; a++)
			for(b = 0; b < n; b++)
				A.t[a][b] = 0, In.t[a][b] = 0,
				init.t[a][b] = 0;
		for(a = 0; a < n; a++) In.t[a][a] = 1;
		
		for(a = 0; a < n; a++) {
			scanf("%s", s);
			for(b = 0; b < n; b++)
				A.t[a][b] = s[b] - '0';
		}
		scanf("%d %d %d", &i, &j, &k);
		printf("%d\n", ans(k+1, i, j, n));
		Floyd_Warshall(n);
	}
	return 0;
}
