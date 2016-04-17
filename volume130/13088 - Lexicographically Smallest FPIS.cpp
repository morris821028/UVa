#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		char s[1024];
		scanf("%s", s);
		n = strlen(s);
		int mark[128] = {}, m = 0;
		for (int i = 0; i < n; i++)
			mark[s[i]]++;
		for (int i = 'a'; i <= 'z'; i++)
			m += mark[i] != 0;
		for (int i = 'a', t = 0; i <= 'z'; i++) {
			if (mark[i]) {
				for (; t < n-m+1; t++)
					putchar(i);
				m--;
			}
		}
		puts("");
	}
	return 0;
}

