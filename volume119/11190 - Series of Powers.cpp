#include <bits/stdc++.h>
using namespace std;

int main() {
	int cases = 0;
	int L, H, K;
	while (scanf("%d %d %d", &L, &H, &K) == 3 && L >= 0) {
		double m = 0, n = 0;
		double t = 0;
		double exp = 0;
		for (int i = H; i >= L; i--) {
			double v = log10(i) * K;
			exp = max(exp, floor(v));
		}
		for (int i = H; i >= L; i--) {
			double v = log10(i) * K - exp;
			t += pow(10, v);
		}
		while (t >= 1)
			t /= 10, exp++;
		if (fabs(t) < 1e-6 && exp == 0)
			exp = 1;
		printf("Case %04d: %.6lfe%010lld\n", ++cases, t, (long long) exp);
	}
	return 0;
}

