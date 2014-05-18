#include <stdio.h>

int main() {
	int testcase, cases = 0;
	int L, M, N;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d %d", &L, &M, &N);
		int LL = L * L;
		long long ret = 0, ways = 1;
		for(int i = 1; i < M; i++) {
			ways *= (LL - i + 1);
			ways %= 10000000000007LL;
		}
		for(int i = M; i <= N; i++) {
			ways *= (LL - i + 1);
			ways %= 10000000000007LL;
			ret += ways;
			ret %= 10000000000007LL;
		}
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
