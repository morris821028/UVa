#include <stdio.h>
#include <stdlib.h>
#define LL long long
#define maxL (10000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
using namespace std;
int mark[maxL];
int P[5050], Pt = 0;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 10000;
    for(i = 2; i < n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            P[Pt++] = i;
        }
    }
}
int main() {
	sieve();
	const long long mod = 1000000007LL;
	int testcase, cases = 0;
	long long N, K;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%lld %lld", &N, &K);
		long long ret1 = 1, ret2 = 1;
		for(int i = 0; i < Pt; i++) {
			long long p = P[i], cnt = 0;
			while(p <= N)
				cnt += N / p, p *= P[i];
			if(cnt < K)
				break;
			ret1 *= cnt/K + 1;
			ret2 *= cnt/(K+1) + 1;
			ret1 %= mod;
			ret2 %= mod;
		}
		printf("Case %d: %lld\n", ++cases, ((ret1 - ret2)%mod + mod)%mod);
	}
	return 0;
}
