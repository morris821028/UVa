#include <stdio.h> 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXN 10000000
#define maxL (10000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL];
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 10000000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
        }
    }
}

long long f[MAXN + 5], phi[MAXN + 5];
const long long mod = 100000007LL;
// f[i] = i!, phi[i] = phi(i!)
long long inv(long long n, long long m) { // get n*? = 1 (mod m)
	long long la = 1, lb = 0, ra = 0, rb = 1;
	long long i = 0, t, mod = m;
	while(n%m) {
		if(!i) {
			la -= n/m*ra, lb -= n/m*rb;
		} else {
			ra -= n/m*la, rb -= n/m*lb;
		}
		i = !i;
		t = n, n = m, m = t%m;
	}
	return i ? (la%mod+mod)%mod : (ra%mod+mod)%mod;
}
int main() {
	sieve();
	
	f[0] = f[1] = phi[1] = phi[2] = 1;
	f[2] = 2;
	for (long long i = 3; i <= MAXN; i++) {
		f[i] = (f[i - 1] * i)%mod;
		if (!GET(i)) {
			phi[i] = phi[i-1] * (i-1) %mod;
		} else {
			phi[i] = phi[i-1] * (i) %mod;
		}
	}
	
	int n, m;
	while (scanf("%d %d", &n, &m) == 2 && n+m) {
		long long ret = phi[m];
		ret = ret * f[n] %mod;
		ret = ret * inv(f[m], mod) %mod;
		ret = (ret - 1 + mod)%mod;
		printf("%lld\n", ret);
	}
	return 0;
}
