#include <bits/stdc++.h> 
using namespace std;
#define MAXL (5000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[MAXL];
int P[500000], Pt = 0;
void sieve() {
    SET(1);
    int n = 5000000;
    for (int i = 2; i <= n; i++) {
        if (!GET(i)) {
            for (int k = n/i, j = i*k; k >= i; k--, j -= i)
            	SET(j);
			P[Pt++] = i;
        }
    }
}
const int64_t MOD = 100000007LL;
int main() {
	sieve();
	int n;
	while (scanf("%d", &n) == 1 && n) {
		int64_t ret = 1;
		for (int i = 0; i < Pt && P[i] <= n; i++) {
			int64_t t = 0;
			int32_t p = P[i], tn = n, tp = p;
			while (tn/p) {
				int64_t a = tn/p;
				t += a*(n%tp+1) + (a)*(a-1)/2*tp;
				tn /= p, tp *= p;
			}
			if (t >= MOD)
				t %= MOD;
			ret = ret * (t+1);
			if (ret >= MOD)
				ret %= MOD;
		}
		printf("%lld\n", ret);
	}
	return 0;
}
