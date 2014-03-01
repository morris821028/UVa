#include<stdio.h>
unsigned long long gcd(unsigned long long x, unsigned long long y) {
	unsigned long long t;
	while(x%y) {
		t = x, x = y, y = t%y;
	}
	return y;
}
main() {
	int s, k;
	while(scanf("%d %d", &s, &k) == 2) {
		unsigned long long U = (2*k), L = (k+1);
		unsigned long long t;
		t = gcd(U, L), U /= t, L /= t;
		L *= k+1;
		t = gcd(U, L), U /= t, L /= t;
		U = L - U;
		t = gcd(U, L), U /= t, L /= t;
		U *= s;
		t = gcd(U, L), U /= t, L /= t;
		if(U%L == 0)
			printf("%llu\n", U/L);
		else
			printf("%llu / %llu\n", U, L);
	}
	return 0;
}
