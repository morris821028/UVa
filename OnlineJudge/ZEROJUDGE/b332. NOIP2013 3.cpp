#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long m, x;
    while (scanf("%d %lld", &n, &m) == 2) {
        long double p1 = LONG_LONG_MIN, p2, sum = 0;
        long double ret = LONG_LONG_MIN;
        long long pp2 = LONG_LONG_MIN, re = LONG_LONG_MIN;
        for (int i = 0; i < n; i++) {
            scanf("%lld", &x);
            sum += x;
            p1 = max(p1, sum);
            if (sum < 0)	sum = 0;
            if (i == 0)    	p2 = p1, pp2 = p1;
            if (p2 > ret)
            	ret = max(ret, p2), re = pp2;
            if (i == 0)		p2 = p1 + p2, pp2 = ((long long)p1 + pp2)%m;
            else {		
            	if (p1 > 0) {
					p2 = max(p2, p1 + p2);
					pp2 = (pp2 + (long long) p1)%m;
				}
			}
        }
        printf("%lld\n", re%m);
    }
    return 0;
}

