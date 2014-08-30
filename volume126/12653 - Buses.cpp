#include <stdio.h>
#include <string.h>

const long long mod = 1000000LL;
struct Matrix {
	long long v[2][2];
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
					ret.v[i][j] = (ret.v[i][j] + v[i][k] * x.v[k][j]%mod)%mod;
		return ret;
	}
	Matrix operator^(const long long& n) const {
		Matrix ret(row, col, 1), x = *this;
		long long y = n;
		while(y) {
			if(y&1)	ret = ret * x;
			y = y>>1, x = x * x;
		}
		return ret;
	}
};

int main() {
    long long N, K, L;
    while (scanf("%lld %lld %lld", &N, &K, &L) == 3) {
        N /= 5;
//        long long dp[120]= {};
//        dp[0] = 1;
//        for (int i = 1; i <= N; i++) {
//            dp[i] = dp[i-1] * K;
//            if (i - 2 >= 0) {
//                dp[i] += dp[i-2] * L;
//            }
//        }
        Matrix A(2, 2, 0);
        A.v[0][0] = K%mod, A.v[0][1] = 1;
        A.v[1][0] = L%mod, A.v[1][1] = 0;
        Matrix M = A ^ N;
        printf("%06lld\n", M.v[0][0]);
    }
    return 0;
}
/*
 $ a_{n} = K a_{n-1} + L a_{n-2} $
 
 25 5 5
 5 1000 1000
 20 17 31
 15 9 2
 */