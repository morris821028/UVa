#include <stdio.h>

int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		int i;
		for (i = n; i >= 1; i--)
			printf("%d\n", i);
	}
	return 0;
}
