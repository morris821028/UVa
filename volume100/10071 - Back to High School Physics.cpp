#include<stdio.h>
int main() {
	long long v, t;
	while(scanf("%lld %lld", &v, &t) == 2)
		printf("%lld\n", 2*v*t);
    return 0;
}
