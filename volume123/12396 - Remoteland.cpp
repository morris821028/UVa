#include <stdio.h> 
#include <algorithm>
using namespace std;
#define maxL (10000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL];
int P[1048576], Pt = 0;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 10000000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            P[Pt++] = i; 
        }
    }
}
long long mpow(long long x, long long y, long long mod) {
	long long ret = 1;
	while(y) {
		if(y&1)
			ret *= x, ret %= mod;
		y >>= 1, x = (x * x)%mod;
	}
	return ret;
}
int main() {
	sieve();
	int n;
	const long long mod = 1000000007LL;
	while(scanf("%d", &n) == 1 && n) {
		long long ret = 1;
		for(int i = 0; i < Pt; i++) {
			long long p = P[i], cnt = 0;
			while(p <= n)
				cnt += n / p, p *= P[i];
			if(cnt < 2)	break;
			ret *= mpow(P[i], cnt/2*2, mod);
			ret %= mod;
		} 
		printf("%lld\n", ret);
	}
	return 0;
}
