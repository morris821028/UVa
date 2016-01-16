#include <stdio.h>
#include <stdlib.h>

int main() {
	long long L;
	while (scanf("%lld", &L) == 1) {
		if (L > 0)
			printf("%lld\n", L*2-1);
		else
			printf("%lld\n", -L*2);
	}
	return 0;
}
