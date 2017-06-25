#include <bits/stdc++.h>
using namespace std;

#define MAXL (10000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[MAXL], P[1000000], Pt = 0;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 10000000;
    for (i = 2; i <= n; i++) {
        if (!GET(i)) {
            for (k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            P[Pt++] = i;
        }
    }
}
void factorize(long long n, vector<long long> &f) {
    for (int i = 0; i < Pt && P[i]*P[i] <= n; i++) {
        if (n%P[i] == 0) {
            while (n%P[i] == 0)
                f.push_back(P[i]), n /= P[i];
        }
    }
    if (n != 1)	f.push_back(n);
}
void factor_gen(int idx, long long x, long long y, vector< pair<long long, int> > &f, long long &ret) {
    if (idx == f.size()) {
//    	printf("%lld %lld\n", x, y);
    	ret += y*x;
        return ;
    }
    for (long long i = 0, a = 1; i <= f[idx].second; i++, a *= f[idx].first)
        factor_gen(idx+1, x*a, y*((f[idx].second-i)*2+1), f, ret);
}
long long YAGCDSUM(long long n) {
    vector<long long> f;
    vector< pair<long long, int> > f2;
    factorize(n, f);
    sort(f.begin(), f.end());
    int cnt = 1;
    for (int i = 1; i <= f.size(); i++) {
        if (i == f.size() || f[i] != f[i-1])
            f2.push_back(make_pair(f[i-1], cnt)), cnt = 1;
        else
            cnt ++;
    }
    long long ret = 0;
    factor_gen(0, 1, 1, f2, ret);
    return ret;
}
int main() {
	sieve();
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		long long n, ret = 0;
		scanf("%lld", &n);
		ret = YAGCDSUM(n);
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}

