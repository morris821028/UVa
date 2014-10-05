#include <stdio.h>

int main() {
	long long a, b, q;
	scanf("%*d");
	while (scanf("%lld %lld %lld", &a, &b, &q) == 3) {
		puts((a * q)%10007 == (b * q)%10007 ? "SAFE" : "BOOM");
	}
	return 0;
}
