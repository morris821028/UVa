#include <stdio.h>

int main() {
	int a, b, c;
	while (scanf("%d %d %d", &a, &b, &c) == 3) {
		int f = a+b > c && b+c > a && c+a > b;
		printf("%d\n", f);
	}
	return 0;
}

