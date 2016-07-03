#include <stdio.h> 

int main() {
	const long long MOD = 1000000007;
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		
		long long ret = 1, sum = 0, x;
		for (int i = 0; i < n; i++) {
			scanf("%lld", &x);
			ret = ret * (x + 1) % MOD;
			sum = (sum + x) % MOD;
		}
		ret -= 1; 	// {}
		ret -= sum; // {A}, {B}, ...
		ret = (ret % MOD + MOD) % MOD;
		printf("%lld\n", ret);
	}
	return 0;
}
/*
3
3
2 1 2
3
2 2 2
3
3 2 3
*/
