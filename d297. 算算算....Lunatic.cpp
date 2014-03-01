#include<stdio.h>
main() {
	long long N, t, U, L;
	while(scanf("%lld", &N) == 1) {
		U = (N*N*N+3*N*N+2*N-(N*(N+1)*(2*N+4)/3))/2;
		t = N / 2;
		L = (t*(N*N+3*N+2)+(t*(t+1)*(4*t-6*N-7))/3)/2;
		printf("%lld\n", U+L);
	}
	return 0;
}
