#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	int cases = 0;
	int n;
	char s[131072];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		scanf("%s", s);
		printf("Case #%d: ", ++cases);
		for (int i = 0; s[i]; i++) {
			if (s[i] == 'E')
				putchar('S');
			else
				putchar('E');
		}
		puts("");
	}
	return 0;
}
