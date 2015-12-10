#include <stdio.h> 
#define MAXL (1000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
using namespace std;
int mark[MAXL], P[131072], Pt;
void sieve() {
    register int i, j, k;
    SET(1), Pt = 0;
    int n = 1000000;
    for (i = 2; i < n; i++) {
        if (!GET(i)) {
            for (k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            P[Pt++] = i;
        }
    }
}
int count(int n, int f) {
	int ret = 0;
	while (n)
		ret += n / f, n /= f;
	return ret;
}
long long mpow(long long x, long long y, long long mod) {
	long long ret = 1;
	while (y) {
		if (y&1)
			ret = ret * x % mod;
		y >>= 1, x = x * x % mod;
	}
	return ret;
}
int main() {
	sieve();
	const long long mod = 1e+9;
	int N;
	while (scanf("%d", &N) == 1) {
		long long ret = 1;
		int c2 = count(N, 2) - count(N, 5);
		int c3 = count(N, 3); 
		ret = ret * mpow(2, c2, mod) %mod * mpow(3, c3, mod) %mod;
		for (int i = 3; i < Pt; i++) {
			
			int c = count(N, P[i]);
			if (c == 0)
				break;
			ret = ret * mpow(P[i], c, mod) % mod;
		}
		printf("%lld\n", ret);
	} 
	return 0;
}
