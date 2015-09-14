#include <stdio.h>

int main() {
	long long s, f, t;
	while (scanf("%lld %lld %lld", &s, &f, &t) == 3) {
		long long x, y, z;
		z = s - t;
		y = f/2 - 4*s + 3*t;
		x = 4*s - f/2 - 2*t;
		if (f%2 == 0 && x >= 0 && y >= 0 && z >= 0)
			printf("%lld\n%lld\n%lld\n", x, y, z);
		else
			puts("0");
	}
	return 0;
}
