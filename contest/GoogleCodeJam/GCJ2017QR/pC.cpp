#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		long long n, m;
		scanf("%lld %lld", &n, &m);
		map<long long, long long> S;
		S[n] = 1;
		long long ret1 = -1, ret2 = -1;
		while (m) {
			pair<long long, long long> e = *S.rbegin();
			S.erase(e.first);
			if (e.second >= m) {
				ret1 = e.first/2, ret2 = (e.first-1)/2;
				break;
			}
			m -= e.second;
			if (e.first%2) {
				long long t = e.first/2;
				S[t] += 2LL*e.second;
			} else {
				long long t = e.first/2;
				S[t] += e.second;
				S[t-1] += e.second;
			}
		}
		printf("Case #%d: %lld %lld\n", ++cases, ret1, ret2);
	}
	return 0;
}
/*
5
1000000000000000000 1000000000000000000
*/

