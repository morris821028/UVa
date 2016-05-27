#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	long long B, D;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lld %lld", &B, &D);
		printf("Case %d: %lld\n", ++cases, (B-1) / D);
	}
	return 0;
}

