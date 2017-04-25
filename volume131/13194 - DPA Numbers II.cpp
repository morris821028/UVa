#include <bits/stdc++.h>
using namespace std;

int P[100000], Pt = 0;
void sieve() {
#define MAXL (1000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
	static int mark[MAXL] = {};
    SET(1);
    int n = 1000000;
    for (int i = 2; i <= n; i++) {
        if (!GET(i)) {
            for (int k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            P[Pt++] = i;
        }
    }
    
}

int main() {
	sieve();
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int64_t n, m;
		scanf("%lld", &n);
		m = n;
		int64_t ret = 1;
		for (int i = 0; i < Pt && P[i]*P[i] <= m; i++) {
			if (m%P[i])
				continue;
			int64_t p = P[i];
			int64_t s = p;
			while (m%p == 0)
				m /= p, s *= p;
			ret *= (s-1) / (p-1);
			if (ret > 2*n)
				break;
		}
		if (m != 1)
			ret *= m+1;
		if (ret == 2*n)
			puts("perfect");
		else if (ret < 2*n)
			puts("deficient");
		else
			puts("abundant");
//		printf("%lld\n", ret);
	}
	return 0;
}
/*
9
999900007063
934053120000
999900003719
349621272000
560431872000
999900001643
999900003863
539630239744
137438691328
*/

