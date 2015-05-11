#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
	int testcase, cases = 0;
	long long C, K, V, x[128];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lld %lld %lld", &C, &K, &V);
		
		long long sum = 0, ret = 0;
		for (int i = 0; i < K; i++) {
			scanf("%lld", &x[i]);
		}
		for (int i = 0; i < K; i++) {
			while (sum < V && sum < x[i] - 1) {
				ret++;
				long long ncoin = sum + 1;
				sum += ncoin * C;
			}
			sum += x[i] * C;
		}
		while (sum < V) {
			ret++;
			long long ncoin = sum + 1;
			sum += ncoin * C;
		}
		printf("Case #%d: %d\n", ++cases, ret);
	}
	return 0;
}
/*

*/
