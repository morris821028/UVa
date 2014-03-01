#include<stdio.h>
int main() {
	long long n;
	while(scanf("%lld", &n) == 1) {
		long long a, b, c, d, e = 0, f, i;
		a = n*(n+1)*(2*n+1)/6;
		b = (n+1)*n/2*(n+1)*n/2 - a;
		c = n*(n+1)/2*n*(n+1)/2;
		d = (n+1)*n/2*(n+1)*n/2*(n+1)*n/2 - c;
		for(i = 1; i <= n; i++)	e += i*i*i*i;
		f = (n+1)*n/2*(n+1)*n/2*(n+1)*n/2*(n+1)*n/2 - e;
		printf("%lld %lld %lld %lld %lld %lld\n", a, b, c, d, e, f);
	}
    return 0;
}
