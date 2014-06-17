#include <stdio.h>
#include <math.h>
int main() {
	long long n;
	while(scanf("%lld", &n) == 1 && n) {
		long long sqr = (long long)sqrt(n);
		if(sqr*sqr == n)
			puts("yes");
		else
			puts("no");
	}
    return 0;
}
