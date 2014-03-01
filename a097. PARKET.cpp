#include<stdio.h>
#include<math.h>
main() {
	long long B, R, a, b, A, D, t;
	while(scanf("%lld %lld", &B, &R) == 2) {
		long long sq = (long long)sqrt(R);
		for(a = 1; a <= sq; a++) {
			if(R%a == 0) {
				b = R/a;
				A = a + b;
				D = 4 * (A*A + 4*B);
				t = (long long)sqrt(D);
				if(t * t == D && (-2*A + t)%8 ==0 ) {
					printf("%lld %lld\n", b + (-2*A + t)/4, a + (-2*A + t)/4);
					break;
				}
			}
		}
	}
	return 0;
}
