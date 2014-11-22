#include <stdio.h>
#include <map>
#include <algorithm>
using namespace std;
long long llgcd(long long x, long long y) {
	long long t;
	while (x%y)
		t = x, x = y, y = t%y;
	return y;
}
int main() {
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		long long ret = 0, x, g;
		map<long long, int> R;
		for (int i = 0; i < n; i++) {
			scanf("%lld", &x);
			map<long long, int> P;
			ret = max(ret, x);
			P[x] = i;
			for (map<long long, int>::iterator it = R.begin(), jt;
				it != R.end(); it++) {
				g = llgcd(it->first, x);
				ret = max(ret, g * (i - it->second + 1));
//				printf("%lld %lld\n", g, (long long)(i - it->second + 1));
				jt = P.find(g);
				if (jt != P.end())
					jt->second = min(jt->second, it->second);
				else
					P[g] = it->second;
			}
			R = P;
//			puts("-----");
		}
		printf("%lld\n", ret);
	}
	return 0;
}
/*
1
5
30 60 20 20 20
*/
