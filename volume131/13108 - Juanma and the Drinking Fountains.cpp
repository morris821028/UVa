#include <bits/stdc++.h>
using namespace std;
/*
A000127 		
	Maximal number of regions obtained by joining n points around a circle by straight lines. 
	Also number of regions in 4-space formed by n-1 hyperplanes.
	(Formerly M1119 N0427)
*/
// (n^4-6*n^3+23*n^2-18*n+24)/24
int main() {
	int testcase;
	long long n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lld", &n);
		long long ret;
		ret = n*n*n*n-6*n*n*n+23*n*n-18*n+24;
		ret /= 24;
		printf("%lld\n", ret);
	}
	return 0;
}

