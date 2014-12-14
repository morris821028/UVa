#include <stdio.h>
#include <string.h>

int main() {
	int testcase;
	char s[131072];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s", s);
		int n = strlen(s);
		if (s[0] == 'W' || s[n-1] == 'B') {
			puts("IMPOSSIBLE");
			continue;
		} // can't split
		
		int kind = 0; // B start.
		int wcnt = 0;
		for (int i = 0; i < n; i++) {
			wcnt += s[i] == 'W';
			if (s[i] == 'W' && kind == 0)
				kind = 1;
			if (s[i] == 'B' && kind == 1)
				kind = 2;
		}
		if (kind == 1) { // B+W+
			printf("%d\n", 1);
			printf("%d", n);
			for (int i = 1; i <= n; i++)
				printf(" %d", i);
			puts("");
		} else {
			printf("%d\n", 2);
			printf("%d %d", wcnt, 1);
			for (int i = 1; i < n - 1; i++) // BW...WW
				if (s[i] == 'W')	printf(" %d", i + 1);
			puts("");
			printf("%d", n - wcnt);
			for (int i = 1; i < n; i++) // BB...BW
				if (s[i] == 'B')	printf(" %d", i + 1);
			printf(" %d\n", n);
		}
	}
	return 0;
}
/*
2
BWBW
BWW
*/
