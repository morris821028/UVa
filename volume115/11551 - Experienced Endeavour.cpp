#include <stdio.h> 
#include <string.h>
const long long mod = 1000LL;
struct Matrix {
	long long v[64][64];
	int row, col; // row x col
	Matrix(int n, int m, long long a = 0) {
		memset(v, 0, sizeof(v));
		row = n, col = m;
		for(int i = 0; i < row && i < col; i++)
			v[i][i] = a;
	}
	Matrix operator*(const Matrix& x) const {
		Matrix ret(row, x.col);
		for(int i = 0; i < row; i++)
			for(int j = 0; j < x.col; j++)
				for(int k = 0; k < col; k++)
					ret.v[i][j] += v[i][k] * x.v[k][j] %mod,
					ret.v[i][j] %= mod;
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
	int testcase, n, m, b, r, a[105];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &n, &r);
		for(int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		Matrix x(n, n), A(n, 1);
		for(int i = 0; i < n; i++)
			A.v[i][0] = a[i];
		for(int i = 0; i < n; i++) {
			scanf("%d", &m);
			while(m--) {
				scanf("%d", &b);
				x.v[i][b] = 1;
			}
		}
		Matrix xr = x ^ r;
		Matrix ret = xr * A;
		for(int i = 0; i < n; i++)
			printf("%lld%c", ret.v[i][0], i == n-1 ? '\n' : ' ');
	}
	return 0;
}
/*
2
2 2
1 2
2 0 1
1 1
2 4
507 692
2 0 1
1 1
*/
