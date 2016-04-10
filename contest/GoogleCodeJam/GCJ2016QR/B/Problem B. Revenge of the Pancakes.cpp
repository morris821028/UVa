#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	char s[1024];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s", s);
		int n = strlen(s), ret = 0;
		for (int i = n-1; i >= 0; i--) {
			if (s[i] == '+')	continue;
			int has = 0, j = 0;
			for (j = 0; j <= i; j++) {
				if (s[j] == '-')	break;
				has = 1;
			}
			if (has) {
				reverse(s, s+j);
				for (int k = 0; k < j; k++) {
					if (s[k] == '-')
						s[k] = '+';
					else
						s[k] = '-';
				}
			}
			ret += has;
			if (s[i] == '+')	continue;
			reverse(s, s+i+1);
			for (int k = 0; k < i+1; k++) {
				if (s[k] == '-')
					s[k] = '+';
				else
					s[k] = '-';
			}
			ret++;
		}
		printf("Case #%d: %d\n", ++cases, ret);
	}
	return 0;
}
/*
5
-
-+
+-
+++
--+-
*/

