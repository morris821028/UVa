#include <stdio.h> 
#include <string.h>
const unsigned long long mod = 1000000000;
struct Matrix {
	unsigned long long v[150][150];
	int row, col; // row x col
	Matrix(int n, int m, long long a = 0) {
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
	void print() {
		for (int i = 0; i < row; i++) {
			printf("[");
			for (int j = 0; j < col; j++) {
				printf("%5llu%c", v[i][j], j == col - 1 ? ']' : ',');
			}
			puts("");
		}
	}
};
int main() {
	int N, M, K;
	while (scanf("%d %d %d", &N, &M, &K) == 3) {
		int state = N * M * 2; // (i, j, dir), dir : (left, right), (up, down)
		Matrix m(state, state), a0(state, 1);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				for (int k = 0; k < N; k++) { // (left, right) -> (up, down)
					if (k == i)	continue;
					m.v[k * M * 2 + j * 2 + 1][i * M * 2 + j * 2 + 0] = 1;
				}
				for (int k = 0; k < M; k++) { // (up, down) -> (left, right)
					if (k == j)	continue;
					m.v[i * M * 2 + k * 2 + 0][i * M * 2 + j * 2 + 1] = 1;
				}
			}
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				a0.v[i * M * 2 + j * 2 + 0][0] = M - 1;
				a0.v[i * M * 2 + j * 2 + 1][0] = N - 1;
			}
		}
		Matrix v = (m ^ K) * a0;
//		v.print();
		unsigned long long ret = 0;
		for (int i = 0; i < v.row; i++) {
			for (int j = 0; j < v.col; j++) {
				ret += v.v[i][j];
				ret %= mod;
			}
		}
		printf("%llu\n", ret);
	}
	return 0;
}
/*
2 2 1
2 2 100 
2 3 1 
2 3 2
1 5 31
1 3 15
2 1 93
1 5 52
4 5 24
4 5 97
4 2 34
1 2 16
4 2 57
1 1 100

8
8
24
36

*/
