#include <stdio.h>

int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		int ret = 0;
		while (n)
			ret += n&1, n >>= 1;
		printf("%d\n", ret);
	}
	return 0;
}

