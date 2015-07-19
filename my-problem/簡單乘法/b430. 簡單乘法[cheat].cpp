#include <bits/stdc++.h> 
using namespace std;
long long mul(long long a, long long b, long long m) {
    long long y = (long long)((double)a*b/m+0.5);
    long long r = (a*b-y*m) % m;
    if (r < 0) r += m;
    return r;
}
int main() {
	long long a, b, m;
	while (scanf("%lld %lld %lld", &a, &b, &m) == 3)
		printf("%lld\n", mul(a, b, m));
	return 0;
}
