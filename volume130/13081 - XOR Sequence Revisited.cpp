#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	scanf("%d", &testcase);
	unsigned long long L, R;
	while (testcase--) {
		scanf("%llu %llu", &L, &R);
		if (L == R) {
			unsigned long long ret = 0;
			for (int i = 1; i < 63; i++) {
				unsigned long long a;
				unsigned long long v = 1LL<<(i+1);
				a = L / v * v + (1LL<<i);
				int odd = a <= L && L < a + (1LL<<i) && (L - a)%2 == 0;
				if (i == 0)	odd++;
				if (odd%2)
					ret |= 1LL<<i;
			}
			if ((L+1)/2%2 == 0)	ret |= 1;
			printf("%llu\n", ret);
		} else if (R - L >= 2) {
			puts("0");
		} else {
			printf("%d\n", R%4 == 0);
		}
	}
	return 0;
}

