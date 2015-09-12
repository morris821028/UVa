#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int a1, a2, b1, b2, c1, c2;
		scanf("%d %d %d", &a1, &b1, &c1);
		scanf("%d %d %d", &a2, &b2, &c2);
		int dx, dy, d;
		d = a1*b2 - a2*b1;
		dx = c1*b2 - c2*b1;
		dy = a1*c2 - a2*c1;
		printf("%d %d\n", dx/d, dy/d);
	}
	return 0;
}