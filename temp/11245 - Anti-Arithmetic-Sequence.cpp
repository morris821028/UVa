#include <stdio.h>
/*
p = 3, a() = {1, 2 , 4, 5, 10, 11, 13, 14, 28, 29 ...}
a(n) = b(n+1) with b(0)=1, b(2n)=3b(n)-2, b(2n+1)=3b(n)-1
https://oeis.org/?language=english
solution by http://bal4u.dip.jp/cpc/anti-arithmetic-sequence/

*/
long long f(long long n, long long p) {
    if (n == 0) return 1;
    return p*f(n/(p-1), p) + n%(p-1) - (p-1);
}
int main() {
	int testcase;
	long long n, p;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lld %lld", &n, &p);
		printf("%lld\n", f(n - 1, p));
	}
	return 0;
}
