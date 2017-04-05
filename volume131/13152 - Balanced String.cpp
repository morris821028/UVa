#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, n, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		int C[131072] = {};
		int flag = 0;
		for (int i = 0; i < n; i++) {
			int x;
			scanf("%d", &x);
			if (x <= n)
				C[x]++;
			else
				flag = 1;
		}
		
		static char s[131072];
		int dep = 0;
		for (int i = 0; i < n && !flag; i++) {
			if (dep == 0) {
				if (C[dep+1])
					dep++, C[dep]--, s[i] = '(';
				else
					flag = 1;
			} else {
				if (C[dep+1])
					dep++, C[dep]--, s[i] = '(';
				else if (C[dep-1])
					dep--, C[dep]--, s[i] = ')';
				else
					flag = 1;
			}
		}
		s[n] = '\0';
		if (dep)
			flag = 1;
		printf("Case %d: ", ++cases);
		if (flag)
			puts("invalid");
		else
			printf("%s\n", s);
	}
	return 0;
}

