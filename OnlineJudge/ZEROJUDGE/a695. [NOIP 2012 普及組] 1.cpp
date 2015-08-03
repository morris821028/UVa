#include <bits/stdc++.h>

int main() {
	long long n;
	scanf("%lld", &n);
	for (long long i = 2; i*i <= n; i++) {
		if (n%i == 0) {
			printf("%d\n", n/i);
			return 0;
		}
	}
	return 0;
}
