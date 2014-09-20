#include <stdio.h> 
#include <string.h>
const unsigned long long mod = 100000007;
struct Matrix {
	unsigned long long v[2][2];
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
};
int main() {
	int testcase, n;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &n);
		Matrix m(2, 2);
		m.v[0][0] = 1, m.v[0][1] = 1;
		m.v[1][0] = 1, m.v[1][1] = 0;
		Matrix x = m ^ n;
		printf("%llu\n", x.v[0][0]);
	}
	return 0;
}
