#include <stdio.h>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
#define maxL (1000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL];
int P[100000], Pt = 0;
int phi[1048576];
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 1000000;
    for (i = 1; i <= n; i++)
    	phi[i] = i;
    for (i = 2; i <= n; i++) {
        if(!GET(i)) {
            for (k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            for (j = i; j <= n; j += i)
            	phi[j] = phi[j]/i * (i-1);
            P[Pt++] = i;
        }
    }
}
vector< pair<long long, int> > factor(long long n) {
	long long on = n;
	vector< pair<long long, int> > R;
	
	for(int i = 0, j; i < Pt && (long long)P[i] * P[i] <= n; i++) {
		if(n%P[i] == 0) {		
			for(j = 0; n%P[i] == 0; n /= P[i], j++);
			R.push_back(make_pair((long long)P[i], j));
		}
	}
	if(n != 1)	R.push_back(make_pair(n, 1));
	return R;
}
void make(int idx, int n, long long m, vector< pair<long long, int> > &v, vector<long long> &ret) {
	if(idx == v.size()) {
		ret.push_back(m);
		return;
	}
	long long a = m, b = v[idx].first;
	for(int i = v[idx].second; i >= 0; i--)
		make(idx + 1, n, a, v, ret), a *= b;
}
long long getPhi(long long n) {
	if (n < 1000000)	return phi[n];
	vector< pair<long long, int> > f = factor(n);
	for (int i = 0; i < f.size(); i++)
		n = n / f[i].first * (f[i].first - 1);
	return n;
}
int main() {
	sieve();
	int testcase, cases = 0, Q;
	long long N, X;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lld %d", &N, &Q);
		vector< pair<long long, int> > f = factor(N);
		vector<long long> fa;
		vector<long long> sum;
		make(0, N, 1, f, fa);
		sum.resize(fa.size(), 0);
		sort(fa.begin(), fa.end());
		for (int i = 0; i < fa.size(); i++) {
			if (i)
				sum[i] = sum[i-1] + getPhi(N / fa[i]);
			else
				sum[i] = getPhi(N / fa[i]);
		}
		printf("Case %d\n", ++cases);
		for (int i = 0; i < Q; i++) {
			scanf("%lld", &X);
			if (X <= 0) {
				puts("0");
				continue;
			}
			long long ret = 0;
			int pos = (int)(lower_bound(fa.begin(), fa.end(), X) - fa.begin());
			if (pos >= fa.size() || fa[pos] > X)	pos--;
			ret = sum[pos];
			printf("%lld\n", ret);
		}
	}
	return 0;
}
/*
2
30 3
1
2
10
11 5
0
1
2
11
15
*/
