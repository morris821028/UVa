#include <bits/stdc++.h>
using namespace std;

#define MAXL (150000>>5)+1
#define GET(x) (mark[(x)>>5]>>((x)&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))

int P[30000], Pt = 0, mark[MAXL];
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 110000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for (k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            P[Pt++] = i;
        }
    }
}

const int MOD = 1e9+7;
int main() {
	sieve();
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		long long n, m;
		scanf("%lld %lld", &n, &m);
		
		long long ret = 0;
		ret = (ret + n)%MOD;

		if (m >= 3) {
			// (2, p) and (p, 2)
			for (int i = 1; i < Pt && P[i]+2 <= n; i++) {
				if (P[i+1] == P[i]+2) {
					long long comb;
					comb = (m-1)*(m-2)/2%MOD;
					comb = (comb * (n - P[i] - 2))%MOD;
					ret = (ret + comb*2)%MOD;
				}
			}
		}
		if (m >= 4) {
			// (2, p, 2)
			for (int i = 1; i < Pt && P[i]+2 <= n; i++) {
				if (GET(P[i]+2))
					continue;
				if (GET(P[i]+4) || (P[i]+4) >= n)
					continue;
				long long comb;
				comb = (m-1)*(m-2)*(m-3)/6%MOD;
				comb = (comb * (n - P[i]-4))%MOD;
				ret = (ret + comb)%MOD;
			}
		}
		
		if (m >= 2) {
			// (p)
			for (int i = 0; i < Pt && P[i] <= n; i++) {
				ret = (ret + (n-P[i])*(m-1)%MOD)%MOD;
			}
		}
		
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
/*
2
3 2
6 3

3
6 10
7 10
8 10

7
22 30
23 1
23 2
23 3
23 4
23 5
23 6
*/
