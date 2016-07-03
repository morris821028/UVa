#include <stdio.h>

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, m;
		scanf("%d %d", &n, &m);
		long long ret = 0;
		ret += (long long) (m - n) * n;
		ret += (long long) (n) * (n-1)/2;
		printf("%lld\n", ret);
	}
	return 0;
}
