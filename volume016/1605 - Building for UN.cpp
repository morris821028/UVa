#include <stdio.h>
// ignore Print a blank line between test cases.
int main() {
	int n, cases = 0;
	while (scanf("%d", &n) == 1) {
		printf("%d %d %d\n", 2, n, n);
		for (int i = 0; i < n; i++, puts(""))
			for (int j = 0; j < n; j++)
				putchar(i < 26 ? i + 'a' : i-26 + 'A');
		puts("");
		for (int i = 0; i < n; i++, puts(""))
			for (int j = 0; j < n; j++)
				putchar(j < 26 ? j + 'a' : j-26 + 'A');
		puts("");
	}
	return 0;
}
