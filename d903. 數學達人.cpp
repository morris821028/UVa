#include<stdio.h>
long long  reduce_fraction(long long *a, long long *b) {
	long long x = *a, y = *b, t;
	while(x%y) {
		t = x, x = y, y = t%y;
	}
	*a /= y, *b /= y;
}
main() {
	long long n, m, t;
	while(scanf("%lld %lld", &n, &m) == 2) {
		if(n < m) t = m, m = n, n = t;
		long long U1 = (2*n-m)*m, U2 = m*m-1, L = 12;
		reduce_fraction(&U1, &L);
		reduce_fraction(&U2, &L);
		unsigned long long Ans = U1 * U2;
		printf("%llu\n", Ans);
	}
	return 0;
}
