#include <stdio.h> 
#include <string.h>
const int mod = 10000;
struct Matrix {
	int v[100][100];
	int row, col; // row x col
	Matrix(int n, int m, int a = 0) {
		memset(v, 0, sizeof(v));
		row = n, col = m;
		for(int i = 0; i < row && i < col; i++)
			v[i][i] = a;
	}
	Matrix operator*(const Matrix& x) const {
		Matrix ret(row, x.col);
		for(int i = 0; i < row; i++) {
			for(int k = 0; k < col; k++) {
				if (v[i][k])
				for(int j = 0; j < x.col; j++) {
					ret.v[i][j] += v[i][k] * x.v[k][j],
					ret.v[i][j] %= mod;
				}
			}
		}
		return ret;
	}
	Matrix operator^(const int& n) const {
		Matrix ret(row, col, 1), x = *this;
		int y = n;
		while(y) {
			if(y&1)	ret = ret * x;
			y = y>>1, x = x * x;
		}
		return ret;
	}
};
int main() {
	int N, L, S, T;
	int x, y;
	while (scanf("%d %d", &N, &L) == 2) {
		scanf("%d %d", &S, &T);
		Matrix m(N, N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < 4; j++) {
				scanf("%d", &x), x--;
				m.v[i][x]++;
			}
		}
		Matrix ret = m ^ L;
		S--, T--;
		printf("%d\n", ret.v[S][T]);
	}
	return 0;
}
/*
2 20
1 1
2 2 2 2
1 1 1 1
2 29
1 1
2 2 2 2
1 1 1 1
2 0
1 1
2 2 2 2
1 1 1 1
2 0
1 2
2 2 2 2
1 1 1 1
3 2
3 1
1 2 2 2
2 1 3 2
2 2 3 1
*/
