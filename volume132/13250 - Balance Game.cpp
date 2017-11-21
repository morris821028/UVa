#include <bits/stdc++.h>
using namespace std;

void exgcd(int32_t x, int32_t y, int32_t &g, int32_t &a, int32_t &b) {
    if (y == 0)
        g = x, a = 1, b = 0;
    else
        exgcd(y, x%y, g, b, a), b -= (x/y) * a;
}

void bound(int64_t b, int64_t g, int64_t l, int64_t r, int64_t &lk, int64_t &rk) {
	// compute l <= b + g * k <= r, k \in [lk, rk]
	if (g > 0) {
		lk = ceil((double) (l-b)/g);
		rk = floor((double) (r-b)/g);
	} else {
		lk = ceil((double) (r-b)/g);
		rk = floor((double) (l-b)/g);
	}
//	printf("%d %d %d %d\n", b, g, lk, rk);
}
int64_t comb(int64_t x, int64_t y, int64_t z, int64_t n) {
	int32_t a, b, g;
	exgcd(x, y, g, a, b);
	if (z%g)	return 0;
	// (a + lcm(x, y)/x * k, b + lcm(x, y)/y * k)
	// ax + by = z
	int64_t a_lk, a_rk, b_lk, b_rk;
	bound(a*(z/g), y/g, -n, n, a_lk, a_rk);
	if (a_lk > a_rk)
		return 0;
	bound(b*(z/g), -x/g, -n, n, b_lk, b_rk);
	if (b_lk > b_rk)
		return 0;
	a_lk = max(a_lk, b_lk);
	a_rk = min(a_rk, b_rk);
	return a_rk-a_lk+1;
}
int main() {
	int n, w;
	int a, b, c;
	while (scanf("%d %d", &n, &w) == 2) {
		scanf("%d %d %d", &a, &b, &c);
		if (a > c)	swap(a, c);
		if (b > c)	swap(b, c);
		int64_t ret = 0;
		int t = n*(a+b);
		for (int i = -n; i <= n; i++) {
			int tw = w+c*i;
			if (tw >= -t && tw <= t)
				ret += comb(a, b, tw, n);
		}
		printf("%lld\n", ret);
	}
	return 0;
}
/*
3  140
20  50  40
3  105
20  50  40
*/
