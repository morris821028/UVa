#include <stdio.h>

int main() {
	scanf("%*d");
	long long n;
	while (scanf("%lld", &n) == 1)
		printf("%d\n", (int)__builtin_popcountll(n));
	return 0;
}
