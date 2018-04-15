#include <bits/stdc++.h>
using namespace std;
const int MAXM = 256;
const int MOD = 1e+9;
struct Matrix {
	static int n;
	int64_t v[MAXM*MAXM];
	void init(int val=0) {
		memset(v, 0, sizeof(v[0])*n*n);
		if (val) {
			for (int i = 0; i < n; i++)
				v[i*n+i] = val;
		}
	}
	
};
void square(Matrix &x) {
	static int64_t trans_v[MAXM*MAXM], v[MAXM*MAXM];
	for (int i = 0; i < Matrix::n; i++) {
		for (int j = 0; j < Matrix::n; j++)
			trans_v[i*Matrix::n+j] = x.v[j*Matrix::n+i];
	}
	for (int i = 0; i < Matrix::n; i++) {
		for (int j = 0; j < Matrix::n; j++) {
			int64_t sum = 0;
			for (int k = 0; k < Matrix::n; k++) {
				sum += x.v[i*Matrix::n+k] * trans_v[j*Matrix::n+k];
				if (sum >= MOD)
					sum %= MOD;
			}
			v[i*Matrix::n+j] = sum;
		}
	}
	memcpy(x.v, v, sizeof(v[0])*Matrix::n*Matrix::n);
}
int Matrix::n = 0;
int main() {
	int n;
	int64_t m;
	static Matrix y;
	while (scanf("%d %lld", &n, &m) == 2) {
		assert(n <= 8);
		const int t = 1<<n;
		Matrix::n = t;
		y.init();
		for (int i = 0; i < t; i++) {
			for (int j = 0; j < t; j++) {
				int dp[16][2] = {};
				dp[0][1] = 1;
				for (int k = 0; k < n; k++) {
					if ((i>>k)&1) {
						if ((j>>k)&1) {
							dp[k+1][0] = dp[k][1];
							dp[k+1][1] = dp[k][0];
						} else {
							dp[k+1][1] = dp[k][1];
						}
					} else {
						if ((j>>k)&1) {
							dp[k+1][0] = dp[k][1];
							dp[k+1][1] = dp[k][0] + dp[k][1];
						} else {
							dp[k+1][1] = dp[k][1];
						}
					}
				}
				y.v[i*t+j] = dp[n][1];
			}
		}

		int64_t A[256] = {}, B[256];
		A[t-1] = 1;		
		
		while (m) {
			if (m&1) {
				memset(B, 0, sizeof(B[0])*t);
				for (int p = 0; p < t; p++) {
					for (int q = 0; q < t; q++) {
						B[q] += y.v[p*t+q] * A[p];
						if (B[q] >= MOD)
							B[q] %= MOD;
					}
				}
				memcpy(A, B, sizeof(B[0])*t);
			}
			square(y), m >>= 1;
		}
		
		int64_t ret = 0;
		for (int i = 0; i < t; i++)
			ret += A[i];
		ret %= MOD;
		printf("%lld\n", ret);
	}
	return 0;
}
/*
2
2
2
4
*/
