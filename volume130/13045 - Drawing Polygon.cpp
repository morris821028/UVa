#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	int N, L;
	const double pi = acos(-1);
	scanf("%d", &testcase);
	while (testcase--) {
		double x, y;
		scanf("%d %d %lf %lf", &N, &L, &x, &y);
		double theta = 0;
		if (cases)
			puts("");
		printf("Case #%d:\n", ++cases);
		for (int i = 0; i < N; i++) {
			printf("%.6lf %.6lf\n", x, y);
			x += L * cos(theta), y += L * sin(theta);
			theta += 2.f * pi / N;
		}
	}
	return 0;
}

