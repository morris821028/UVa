#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int A, B;
		double p, q;
		scanf("%d %d", &A, &B);
		if (A == 0 && B == 0)
			p = q = 0;
		else if (B%2 == 0)
			p = 1, q = 0;
		else
			p = 0, q = 1;
		printf("Case %d: %.3lf %.3lf\n", ++cases, p, q);
	}
	return 0;
}

