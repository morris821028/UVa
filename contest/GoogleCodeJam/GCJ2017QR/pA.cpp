#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0, K;
	char s[1024];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s %d", s, &K);
		int n = strlen(s);
		int ret = 0, valid = 0;
		for (int i = 0; i < n; i++) {
			if (s[i] == '+')
				continue;
			if (i+K <= n) {
				ret++;
				for (int j = 0; j < K; j++) {
					if (s[i+j] == '-')
						s[i+j] = '+';
					else
						s[i+j] = '-';
				}
			}
		}
		valid = 1;
		for (int i = 0; i < n; i++)
			valid &= s[i] == '+';
		if (valid)
			printf("Case #%d: %d\n", ++cases, ret);
		else
			printf("Case #%d: IMPOSSIBLE\n", ++cases);
	}
	return 0;
}

