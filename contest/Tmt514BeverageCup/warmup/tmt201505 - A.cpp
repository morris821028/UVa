#include <stdio.h>

long long mpow(long long x, long long y, long long mod) {
	long long ret = 1;
	while (y) {
		if (y&1)
			ret = (ret * x)%mod;
		y >>= 1, x = (x * x)%mod;
	}
	return ret;
}
int main() {
	int testcase;
	int n, p[128];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n); 
		for (int i = 0; i < n; i++)
			scanf("%d", &p[i]);
			
		int ret = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j)
					continue;
				if (mpow(p[i], (p[j]-1)/2, p[j]) == 1)
					ret++;
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
