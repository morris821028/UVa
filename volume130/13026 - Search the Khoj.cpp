#include <bits/stdc++.h>

int main() {
	int testcase, cases = 0, n;
	char s[1024][16], sq[16];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%s", s[i]);
		printf("Case %d:\n", ++cases);
		scanf("%s", sq);
		for (int i = 0; i < n; i++) {
			int diff = 0;
			for (int j = 0; sq[j] || s[i][j]; j++)
				diff += sq[j] != s[i][j];
			if (diff <= 1)
				printf("%s\n", s[i]);
		}
	}
	return 0;
}
