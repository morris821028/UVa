#include <bits/stdc++.h> 
using namespace std;


// https://en.wikipedia.org/wiki/Ellipse#Circumference
int main() {
	int testcase, cases = 0;
	const double pi = acos(-1);
	scanf("%d", &testcase);
	while (testcase--) {
		double a, b;
		scanf("%lf %lf", &b, &a);
		const double e = sqrt(1 - b*b/a/a);
		double sum = 1;
		double p = 1, ep = 1;
		for (int i = 1; i < 10000; i += 2) {
			ep = ep * e*e;
			p *= ((double) i*i) / ((i+1)*(i+1));
			sum -= p * ep / i;
		}
		sum = sum * (2 * pi * a);
		printf("Case %d: %.12lf\n", ++cases, sum);
	}
	return 0;
}

