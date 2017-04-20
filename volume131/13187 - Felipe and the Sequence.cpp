#include <bits/stdc++.h>
using namespace std;

/*
a_i = \frac{1}{\sqrt{i} + \sqrt{i+1}}
	= \sqrt{i+1} - \sqrt{i}

\sum_{i=1}{m} a_i = n
=> \sqrt{m+1}-1 = n
=> m = (n+1)^2 -1
*/
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		long long n;
		scanf("%lld", &n);
		printf("%lld\n", (n+1)*(n+1)-1);
	}
	return 0;
}

