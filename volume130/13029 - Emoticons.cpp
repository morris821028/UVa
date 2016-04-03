#include <bits/stdc++.h>
using namespace std;

char s[131072];
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s", s);
		int n = strlen(s);
		int ret = 0;
		int h1 = 0, h2 = 0, h3 = 0;
		for (int i = 0; i < n; i++) {
			if (s[i] == '^' && h2) {
				h2--, ret++;
			} else if (s[i] == '^') {
				if (h3 && ret)
					h2++, h3--;
				else
					h1++;
			} else if (s[i] == '_' && h1) {
				h1--, h2++;
			} else if (s[i] == '_') {
				if (ret > h3)
					h3++;
			}
		}
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}

