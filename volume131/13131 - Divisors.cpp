#include <bits/stdc++.h>
using namespace std;

#define MAXL (50000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[MAXL], P[50000], Pt = 0;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 46340;
    for (i = 2; i <= n; i++) {
        if (!GET(i)) {
            for (k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            P[Pt++] = i;
        }
    }
}

void factorize(int n, vector<int> &f) {
    for (int i = 0; i < Pt && P[i]*P[i] <= n; i++) {
    	if (n%P[i] == 0) {
    		while (n%P[i] == 0)
    			f.push_back(P[i]), n /= P[i];
    	}
    }
    if (n != 1)	f.push_back(n);
}
void factor_gen(int idx, long long x, vector< pair<long long, int> > &f, vector<long long> &ret) {
    if (idx == f.size()) {
        ret.push_back(x);
        return ;
    }
    for (long long i = 0, a = 1; i <= f[idx].second; i++, a *= f[idx].first)
        factor_gen(idx+1, x*a, f, ret);
}
int main() {
	sieve();
	
	int testcase, N, K;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &N, &K);
		if (K == 1) {
			printf("0\n");
			continue;
		}
		vector<int> Nf;
		map<int, int> NR;
		factorize(N, Nf);
		for (auto e : Nf)
			NR[e]++;
			
		vector< pair<long long, int> > F;
		vector<long long> ret;
		for (auto e : NR)
			F.push_back(make_pair(e.first, e.second));
		factor_gen(0, 1, F, ret);
		long long sum = 0;
		for (auto e : ret) {
			if (e % K)
				sum += e;
		}
		printf("%lld\n", sum);
	}
	return 0;
}

