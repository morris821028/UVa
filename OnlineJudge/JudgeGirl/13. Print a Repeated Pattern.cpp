#include <stdio.h>

int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		int i, j;
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= i; j++) {
				printf("%d", j);
			}
		}
		puts("");
	}
	return 0;
}
