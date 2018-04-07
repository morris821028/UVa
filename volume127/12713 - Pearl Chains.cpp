#include <bits/stdc++.h>
using namespace std;
/*
Lucas's theorem: https://en.wikipedia.org/wiki/Lucas%27s_theorem
*/
const int P = 1000003;
int64_t powX[P], powY[P], powZ[P];
int64_t f[P<<1], invf[P<<1];
int64_t mpow(int64_t x, int64_t y, int64_t mod) {
	int64_t ret = 1;
	while (y) {
		if (y&1)
			ret = ret*x%mod;
		y >>= 1, x = x*x%mod;
	}
	return ret;
}

void buildPow(int64_t pow[], int64_t x) {
	pow[0] = 1;
	x %= P;
	int64_t y = 1;
	for (int i = 1; i < P; i++) {
		y = y * x;
		if (y >= P)	y %= P;
		pow[i] = y;
	}
}
int64_t C(int n, int m) {
	return f[n]*invf[m]*invf[n-m]%P;
}
void build() {
	f[0] = invf[0] = 1;
	int n = 2*P;
	for (int i = 1; i < n; i++)
		f[i] = f[i-1]*i%P;
	for (int i = 1; i < n; i++)
		invf[i] = invf[i-1]*mpow(i, P-2, P)%P;
}
int main() {
	build();
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int64_t A, B, X, Y, Z;
		scanf("%lld %lld %lld %lld %lld", &A, &B, &X, &Y, &Z);

		buildPow(powX, X);
		buildPow(powY, Y);
		buildPow(powZ, Z);

		int64_t ret = 1;
		while (A || B) {
			int64_t a = A%P, b = B%P;
			int64_t mn = min(a, b), tmp = 0;
			for (int i = 0; i <= mn; i++)
				tmp += C(a+b-i, a-i)*C(b, i)*powX[a-i]%P*powY[b-i]*powZ[i]%P;
			ret = ret*tmp%P;
			A /= P, B /= P;
		}
		printf("%lld\n", ret);
	}
	return 0;
}
/*
5
1 1 1 1 1
2 3 1 1 1
1 1 1 2 1
10 10 10 10 10
100 100 100 100 100
*/
