#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
#define maxL (10000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL];
int P[32767], Pt = 0;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 50000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            P[Pt++] = i;
        }
    }
}
vector< pair<long long, int> > factor(long long n) {
	long long on = n;
	vector< pair<long long, int> > R;
	
	for(int i = 0, j; i < Pt && P[i] * P[i] <= n; i++) {
		if(n%P[i] == 0) {		
			for(j = 0; n%P[i] == 0; n /= P[i], j++);
			R.push_back(make_pair(P[i], j));
		}
	}
	if(n != 1)	R.push_back(make_pair(n, 1));
	return R;
}
long long diff, L, W, K;
void make(int idx, long long n, long long m, vector< pair<long long, int> > &v) {
	if(idx == v.size()) {
		// LCM(n, m) = K
		if(n < m)
			swap(n, m);
		if(n - m > diff && n < K)
			diff = n - m, L = n, W = m;
		return;
	}
	long long a = m, b = v[idx].first;
	long long vv = 1;
	for(int i = v[idx].second; i > 0; i--)
		vv *= b;
	for(int i = v[idx].second; i >= 0; i--)
		make(idx + 1, n * (i ? vv : 1), a, v), a *= b;
}
int main() {
	sieve();
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%lld", &K);
		vector< pair<long long, int> > ff;
		ff = factor(K);
		diff = -1;
		make(0, 1, 1, ff);
		printf("Case %d: ", ++cases);
		if(diff == -1)
			puts("Impossible");
		else
			printf("%lld %lld\n", L, W);
	}
	return 0;
}
