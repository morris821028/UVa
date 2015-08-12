#include <bits/stdc++.h> 
using namespace std;

int main() {
	long long n, m, a;
	while (scanf("%lld %lld %lld", &n, &m, &a) == 3) {
		long long bx = (n/a) * (m/a);
		long long rx = n%a, ry = m%a;
		int fx = 0, fy = 0;
		if (rx)	bx += m/a, fx = 1;
		if (ry)	bx += n/a, fy = 1;
		bx += fx && fy;
		printf("%lld\n", bx);
	}
	return 0;
}
