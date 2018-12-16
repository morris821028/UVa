#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		double A, B;
		scanf("%lf %lf", &A, &B);
		int t = A*10 / (B-A) + 10;
		printf("%d\n", t);
	}
	return 0;
}
/*
 3
10  20
10  21
10  19
*/
