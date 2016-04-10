#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		long long n;
		scanf("%lld", &n);
		if (n == 0) {
			printf("Case #%d: INSOMNIA\n", ++cases);
			continue;
		}
		int has[128] = {}, ten = 10;
		long long on = n;
		while (1) {
			static char buf[32];
			sprintf(buf, "%lld", n);
			for (int i = 0; buf[i]; i++) {
				if (has[buf[i]] == 0) {
					ten--, has[buf[i]] = 1;
				}
			}
			if (ten == 0)
				break;
			n += on;
		}
		printf("Case #%d: %lld\n", ++cases, n);
	}
	return 0;
}

