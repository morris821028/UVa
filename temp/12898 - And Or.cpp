#include <stdio.h>

long long f(long long u, int i) {
	if ((u>>i)&1) {
		return ((u>>(i+1))<<i) + (u&((1LL<<i)-1)) + 1;
	} else {
		return ((u>>(i+1))<<i);
	}
}
int main() {
	int testcase, cases = 0;
	long long retAND, retOR;
	long long sa, sb, a, b;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lld %lld", &a, &b);
		retAND = retOR = 0;
		for (int i = 0; i < 63; i++) {
			sb = f(b, i), sa = f(a - 1, i);
			if (sb - sa > 0)	
				retOR |= 1LL<<i;
			if (sb - sa == b - a + 1)
				retAND |= 1LL<<i;
		}
		printf("Case %d: %lld %lld\n", ++cases, retOR, retAND);
	}
	return 0;
}
