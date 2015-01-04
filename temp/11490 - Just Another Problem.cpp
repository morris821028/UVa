#include <stdio.h>
#include <math.h>
const long long mod = 100000007LL;
long long mul(long long a, long long b, long long mod) {
	long long ret = 0;
	for( ; b != 0; b>>=1, (a<<=1)%=mod)
		if(b&1) (ret += a) %= mod;
	return ret;
}
int main() {
	long long S;
	while(scanf("%lld", &S) == 1 && S) {
		long long sq = (long long)sqrt(S + 0.5);
		long long t, n, f = 0;
		for(t = 1; t <= sq; t++) {
			if((S/t - 6*t)/7 <= 0)
				break;
			if(S%t == 0) {
				if((S / t - 6*t)%7 == 0) {
					n = ((S / t) - 6*t) / 7;
					printf("Possible Missing Soldiers = %lld\n", mul(mul(n, n, mod), 2, mod));
					f = 1;
				}
			}
		}
		if(!f)
			puts("No Solution Possible"); 
		puts("");
	}
	return 0;
}
// (2*t + n)*(3*t + 2*n) = S + 2 * n * n
// S = 7nt + 6t^2 = t(7n + 6t)
/*
96
102
11100
0
*/

