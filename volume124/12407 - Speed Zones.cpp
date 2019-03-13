#include <bits/stdc++.h> 
using namespace std;
// Lagrange multiplier
/*
 minimize f(x) = \sum \sqrt{100^2 + x_i^2} / s_i,
 subject to g(x) = \sum x_i = D
 f(x) - \lambda g(x) = 0
 => x_i = 100 s_i \lambda / \sqrt{1-s_i^2 \lambda^2}
 */
int main() {
	int testcase;
	int cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		double d, s[105];
		int n;
		scanf("%d %lf", &n, &d);
		for (int i = 0; i < n; i++)
			scanf("%lf", &s[i]), s[i] /= 100;
		d /= 100;
		double l = 0, r = 1 / s[0];
		for (int i = 1; i < n; i++)
			r = min(r, 1 / s[i]);
		for (int it = 0; it < 100; it++) {
			double lambda = (l+r)/2;
			double sum = 0;
			for (int i = 0; i < n; i++) {
				double xi = lambda*s[i] / sqrt(1 - s[i]*s[i]*lambda*lambda);
				sum += xi;
			}
			if (sum > d)
				r = lambda;
			else
				l = lambda;
		}

		double ret = 0;
		for (int i = 0; i < n; i++) {
			double lambda = l;
			double xi = lambda*s[i] / sqrt(1 - s[i]*s[i]*lambda*lambda);
			ret += sqrt(1 + xi*xi)/s[i];
		}
		printf("Case %d: %.9lf\n", ++cases, ret);
		
	}
	return 0;
}
/*
2
1  0
50
3  400
10  10  10
*/
