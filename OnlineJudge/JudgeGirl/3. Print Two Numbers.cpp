#include <stdio.h>

int main() {
	int a, b;
	while (scanf("%d %d", &a, &b) == 2)
		printf("%d\n%d\n", b, a);
	return 0;
}

