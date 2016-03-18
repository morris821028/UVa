#include <bits/stdc++.h>
using namespace std;

int main() {
	const double pi = acos(-1);
	double R, V;
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lf %lf", &R, &V);
		printf("Case %d: %.8lf\n", ++cases, pi / 2 * R / V);
	}
	return 0;
}

