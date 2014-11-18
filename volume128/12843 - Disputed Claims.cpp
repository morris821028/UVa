#include <stdio.h>
#include <math.h>
#include <vector>
using namespace std;
struct E {
	long long a, b, c;
	E(long long x=0, long long y=0, long long z=0):
		a(x), b(y), c(z) {}
};
int main() {
	int testcase, cases = 0;
	long long n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lld", &n);
		n *= 2;
		long long a, b, c, c2;
		vector<E> ret;
		for (long long i = 1; i*i <= n; i++) {
			if (n%i == 0) {
				a = i, b = n/i;
				c2 = a*a + b*b, c = sqrt(c2);
				if (c * c == c2)
					ret.push_back(E(a, b, c));
			}
		}
		printf("Case %d: %d\n", ++cases, (int) ret.size());
		for (int i = 0; i < ret.size(); i++)
			printf("(%lld,%lld,%lld)\n", ret[i].a, ret[i].b, ret[i].c);
	}
	return 0;
}
/*
4
210
1000
2400
3360
*/
