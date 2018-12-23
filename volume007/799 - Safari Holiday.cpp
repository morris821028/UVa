#include <bits/stdc++.h>
using namespace std;

int valid(int64_t n, int64_t k, int64_t kmax) {
	return k >= 2 && k <= kmax && n%k == 0 && (n-1)%(k-1) == 0;
}
int main() {
	int64_t n, kmax;
	while (scanf("%lld %lld", &n, &kmax) == 2) {
		int sq = sqrt(n);
		int64_t ret = -1;
		for (int64_t i = 1; i <= sq; i++) {
			if (n%i == 0) {
				if (valid(n, i, kmax))
					ret = max(ret, i);
				if (valid(n, n/i, kmax))
					ret = max(ret, n/i);
			}
		}

		if (n == 1) {
			printf("%d persons/group, 1 day\n", n);
		} else if (ret >= 0) {
			int64_t day = (n-1)/(ret-1);
			printf("%lld persons/group, %lld day%s\n", ret, day, day > 1 ? "s" : "");
		} else {
			puts("No solution");
		}
	}
	return 0;
}
