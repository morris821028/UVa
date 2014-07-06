#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

struct Matrix {
	long long v[2][2];
	Matrix(long long a = 0) {
		memset(&v, 0, sizeof(v));
		for(int i = 0; i < 2; i++)
			v[i][i] = a;
	}
};
const long long mod = 1000000007LL;
Matrix multiply(Matrix x, Matrix y) {
	Matrix z;
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++)
			for(int k = 0; k < 2; k++) {
				z.v[i][j] += x.v[i][k] * y.v[k][j] %mod;
				z.v[i][j] %= mod;
			}
	return z;
}
Matrix pow(Matrix x, long long y) {
	Matrix v(1);
	while(y) {
		if(y&1)
			v = multiply(v, x);
		y = y>>1, x = multiply(x, x); 
	}
	return v;
}
int main() {
	int testcase;
	long long N, X, M, Y, K;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%lld %lld %lld %lld %lld", &N, &X, &M, &Y, &K);
		Matrix mm, na, nb, nc;
		mm.v[0][0] = mm.v[0][1] = mm.v[1][0] = 1;
		na = pow(mm, N);
		nb = pow(mm, M);
		nc = pow(mm, K);
		long long a1, b1, c1, a2, b2, c2;
		long long d, dx, dy;
		a1 = na.v[0][0], b1 = na.v[1][0], c1 = X;
		a2 = nb.v[0][0], b2 = nb.v[1][0], c2 = Y;
		d = a1 * b2 - a2 * b1;
		dx = X * b2 - Y * b1, dy = a1 * Y - a2 * X;
		if(d == 0 || dx%d || dy%d || dx/d < 0 || dy/d < 0)
			puts("Impossible");
		else {
			long long a = dx/d, b = dy/d;
			printf("%lld\n", (a * nc.v[0][0]%mod + b * nc.v[1][0]%mod)%mod);
		}
//		printf("%lld A + %lld B = %lld\n", na.v[0][0], na.v[1][0], X);
//		printf("%lld A + %lld B = %lld\n", nb.v[0][0], nb.v[1][0], Y);
//		printf("%lld A + %lld B = ????\n", nc.v[0][0], nc.v[1][0]);
	}
	return 0;
}
