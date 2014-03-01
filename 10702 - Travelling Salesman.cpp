#include <stdio.h>
#include <string.h>
typedef struct {
    int v[100][100];
}Matrix;
Matrix A, one, zero;
int max(int x, int y) {
	return x > y ? x : y;
}
Matrix multiply(Matrix *x, Matrix *y, int n) {
	static int i, j, k;
	static Matrix tmp;
	tmp = zero;
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			for(k = 0; k < n; k++) {
				tmp.v[i][k] = max(x->v[i][j] + y->v[j][k], tmp.v[i][k]);
			}
		}
	}
	return tmp;
}
Matrix DandC(int n, int k) {
	Matrix x = zero, y = A;
	while(k) {
		if(k&1) {
			if(memcmp(&x, &zero, sizeof(x)) == 0)
				x = y;
			else
				x = multiply(&x, &y, n);
		}
		y = multiply(&y, &y, n);
		k >>= 1;
	}
	return x;
}
int main() {
	int C, S, E, T;
	int i, j;
	while(scanf("%d %d %d %d", &C, &S, &E, &T) == 4) {
		if(C == 0 && S == 0 && E == 0 && T == 0)
			break;
		memset(&A, 0, sizeof(Matrix));
		memset(&one, 0, sizeof(Matrix));
		memset(&zero, 0, sizeof(Matrix));
        for(i = 0; i < C; i++) 
			one.v[i][i] = 1;
		for(i = 0; i < C; i++)
			for(j = 0; j < C; j++)
				scanf("%d", &A.v[i][j]);
		Matrix result = DandC(C, T);
		int ed, best = 0;
		while(E--) {
			scanf("%d", &ed);
			if(best < result.v[S-1][ed-1])
				best = result.v[S-1][ed-1];
		}
		printf("%d\n", best);
	}
    return 0;
}
