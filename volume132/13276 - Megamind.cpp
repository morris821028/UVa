#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	int64_t E, P, K, R;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lld %lld %lld %lld", &E, &P, &K, &R);
		printf("Case %d: ", ++cases);
		if (P*K <= R) {
			int64_t t = (E+P-1)/P;
			printf("%lld\n", t <= K ? t : -1);
		} else {
			int64_t RT = P*K-R;
			int64_t r = (E-P*K)/RT;
			if (r < 0)	r = 0;
			int64_t ret = r*K;
			E -= r*RT;
			while (E > P*K)
				ret += K, E -= RT;
			ret += (E+P-1)/P;
			printf("%lld\n", ret);
		} 
	}
	return 0;
}
/*
4
12  4  3  2
9  4  2  7
13  4  3  1
13  4  3  50
*/
