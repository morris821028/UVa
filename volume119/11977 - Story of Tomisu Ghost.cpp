#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
#define maxL (100005>>5)+1
#define GET(x) (mark[(x)>>5]>>((x)&31)&1)
#define SET(x) (mark[(x)>>5] |= 1<<((x)&31))
int mark[maxL];
int P[100000], Pt = 0;
void sieve() {
    register int i, j, k, l;
    SET(1);
    int n = 100000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(j = i + i; j <= n; j += i)
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
		x = (x*x) %mod;
		y >>= 1;
	}
	return ret;
}
int main() {
	sieve();
	const long long mod = 10000019LL;
	int testcase, n, t, cases = 0;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &n, &t);
		int solvable = 0;
		long long ret = 1;
		for(int i = 0; i < Pt && P[i] <= n; i++) {
			int cnt = 0;
			long long v = P[i];
			do {
				cnt += n / v;
				v *= P[i];
			} while(v <= n);
			solvable |= cnt/t > 0;
			ret *= mpow(P[i], cnt/t, mod);
			ret %= mod;
		}
		printf("Case %d: ", ++cases);
		if(solvable)
			printf("%lld\n", ret);
		else
			puts("-1");
	}
	return 0;
}
