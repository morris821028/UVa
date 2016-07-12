#include <bits/stdc++.h>
using namespace std;

int main() {
	int p, a, b, c, d, n;
	while (scanf("%d %d %d %d %d", &p, &a, &b, &c, &d) == 5) {
		scanf("%d", &n);
		double mx = -1e+30, ret = 0;
		double tsa = sin(a), tca = cos(a);
		double tsb = sin(c), tcb = cos(c);
		double sin1 = sin(a+b), cos1 = cos(a+b);
		double cos2 = cos(c+d), sin2 = sin(c+d);
		for (int i = 1; i <= n; i++) {
			double f = p * (sin1 + cos2 + 2);
			ret = max(ret, mx - f);
			mx = max(mx, f);
			
			double t1, t2;
			t1 = sin1 * tca + cos1 * tsa;
			t2 = cos1 * tca - sin1 * tsa;
			sin1 = t1, cos1 = t2;
			
			t1 = sin2 * tcb + cos2 * tsb;
			t2 = cos2 * tcb - sin2 * tsb;
			sin2 = t1, cos2 = t2;
		}
		printf("%.8lf\n", ret);
	}
	return 0;
}

