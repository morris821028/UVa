#include <bits/stdc++.h>
using namespace std;
 
int main() {
	int64_t n, b;
	while (scanf("%lld %lld", &n, &b) == 2) {
		if (n == 0 && b == 0)
			break;
		int64_t p = b;
		for (int i = 2; i*i <= b; i++) {
			if (b%i == 0) {
				p = i, b /= i;
				while (b%i == 0)
					b /= i;
			}
		}
		if (b != 1)
			p = b;

		int64_t ret = 0;
		for (int64_t i = p; i < n; i *= p) {
			int64_t a = n/i-1;
			ret += (a+1)*a/2*i + (n%i+1)*(n/i);
		}
		printf("%lld\n", ret);
	}
	return 0;
}
