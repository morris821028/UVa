#include <stdio.h>

int main() {
	unsigned long long n;
	while (scanf("%llu", &n) == 1) {
		printf("%d\n", __builtin_popcountll(n));	
	}
	return 0;
}

