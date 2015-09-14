#include <stdio.h>

int main() {
	int n, x;
	while (scanf("%d %d", &n, &x) == 2) {
		int ret = 1;
		if (n == 0)	ret = 0;
		while (x--)	ret *= n;
		printf("%d\n", ret);
	}
	return 0;
}

