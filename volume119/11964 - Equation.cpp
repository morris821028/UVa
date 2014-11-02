#include <stdio.h> 
#include <vector>
using namespace std;

#define maxL (150>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL];
int P[150], Pt = 0;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 150;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            P[Pt++] = i;
        }
    }
}
long long mulmod(long long a, long long b, long long mod) {
	long long ret = 0;
	for ( ; b != 0;b>>=1, (a<<=1) %= mod)
		if (b&1)	(ret += a) %= mod;
	return ret;
}
long long inv(long long n, long long m) { // get n*? = 1 (mod m)
    long long la = 1, lb = 0, ra = 0, rb = 1;
    long long i = 0, t, mod = m;
    while(n%m) {
        if(!i) {
            la -= n/m*ra;
            lb -= n/m*rb;
        } else {
            ra -= n/m*la;
            rb -= n/m*lb;
        }
        i = !i;
        t = n, n = m, m = t%m;
    }
    return i ? (la%mod+mod)%mod : (ra%mod+mod)%mod;
}
long long chinese_remainder(int n, long long m[], long long a[]) {
    long long M = 1, ret = 0;
    for(int i = 0; i < n; i++)
        M *= m[i];
    for(int i = 0; i < n; i++) {
        ret += a[i] * inv(M/m[i], m[i]) %M * (M/m[i]);
        ret %= M;
    }

    return (ret%M + M)%M;
}
vector< pair<int, int> > factor(long long n) {
	vector< pair<int, int> > R;
	
	for(int i = 0, j; i < Pt && P[i] * P[i] <= n; i++) {
		if(n%P[i] == 0) {		
			for(j = 0; n%P[i] == 0; n /= P[i], j++);
			R.push_back(make_pair(P[i], j));
		}
	}
	if(n != 1)	R.push_back(make_pair(n, 1));
	return R;
}
long long mpow(long long x, long long y) {
	long long ret = 1;
	for (int i = 0; i < y; i++)
		ret *= x;
	return ret;
}
vector<long long> dp[37];
int main() {
	sieve();
	for (int i = 0; i < Pt; i++) {
		long long m = P[i];
		int p = 0;
		for (m = P[i], p = 0; m * P[i] <= 1e+15; p++, m *= P[i]);
		dp[i].resize(100005, 0);
		dp[i][0] = 1;
		for (int j = 1; j <= 100000; j <<= 1) {
			for (int k = j; k <= 100000; k++)
				dp[i][k] = (dp[i][k] + dp[i][k - j])%m;
		}
	}
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int K;
		long long M;
		scanf("%d %lld", &K, &M);
		vector< pair<int, int> > f = factor(M);
		long long m[35], a[35];
		for (int i = 0; i < f.size(); i++) {
			for (int j = 0; j < Pt; j++)
				if (f[i].first == P[j])
					m[i] = mpow(P[j], f[i].second), a[i] = dp[j][K] % m[i];
		}
		long long ret = chinese_remainder(f.size(), m, a);
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
