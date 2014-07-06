#include <stdio.h> 
#include <string.h>
const long long mod = 1000000007LL;
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
	int testcase, n, d, a[105];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &n, &d);
		d--;
		for(int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		Matrix x(n, n), A(n, 1);
		for(int i = 0; i < n; i++)
			A.v[i][0] = a[n-i-1];
		for(int i = 0; i < n; i++)
			x.v[0][i] = 1;
		for(int i = 1; i < n; i++) {
			for(int j = i+1; j < n; j++) {
				x.v[i][j] = 1;
			}
			x.v[i][0] = 1;
		}
		Matrix y = x ^ d;
		Matrix r = y * A;
		for(int i = r.row-1; i >= 0; i--) { 
			printf("%lld", r.v[i][0]);
			if(i)	putchar(' ');
		} 
		puts("");
	}
	return 0;
}
/*
3
3 1
1 1 2
3 2
1 1 2
3 3
1 1 2

Sample Input
3
3 7
1 2 3
2 2
4 5
2 1
1 10

Sample Output
129 189 277
5 9
1 10
*/
