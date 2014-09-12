#include <stdio.h> 
#include <string.h>
const unsigned long long mod = 1LLU<<32;
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
};
int main() {
	int testcase, cases = 0, base, score;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &base, &score);
		printf("Case %d: ", ++cases);
		int N = (base - 1) * (base - 1);
		
		unsigned long long dp[64][64] = {}; // [sum][tail_digit] = #way 
		for (int i = 0; i <= N; i++)
			dp[0][i] = 1;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < base; j++) {
				for (int k = 0; k < base; k++) {
					int d = (j - k) * (j - k);
					if (i + d > N || j == k)
						continue;
					dp[i+d][k] += dp[i][j];
					dp[i+d][k] %= mod;
				}
			}
		}
		
		if (score <= N) {
			unsigned long long ret = 0;
			for (int i = 1; i < base; i++)
				ret = (ret + dp[score][i])%mod;
			printf("%llu\n", ret);
			continue;
		}
		int r, c;
		r = c = (base - 1) * (base - 1) * base;
		Matrix x(r, c), y(c, 1);
		for (int i = 1; i <= N; i++)
			for (int j = 0; j < base; j++)
				y.v[(i-1) * base+j][0] = dp[i][j];
		for (int i = base; i < r; i++)
			x.v[i - base][i] = 1;
		for (int i = 0; i < base; i++) {
			for (int j = 0; j < base; j++) {
				if (i == j)	continue;
				int d = N - (i - j) * (i - j);
				x.v[(N-1)*base + i][d*base + j] = 1;
			}
		}
//		puts("");
//		for (int i = 0; i < r; i++, puts(""))
//			for (int j = 0; j < c; j++)
//				printf("%lld ", x.v[i][j]);
//		for (int i = 0; i < c; i++, puts(""))
//				printf("%lld ", y.v[i][0]);
		Matrix z = (x ^ (score - N)) * y;
		unsigned long long ret = 0;
		for (int i = 1; i < base; i++)
			ret = (ret + z.v[(N-1) * base + i][0])%mod;
		printf("%llu\n", ret);
	}
	return 0;
}
