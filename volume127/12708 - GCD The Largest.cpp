#include <stdio.h>

int main() {
	scanf("%*d");
	for(long long n; scanf("%lld", &n) == 1;)
		printf("%lld\n", n / 2);
	return 0;
}
