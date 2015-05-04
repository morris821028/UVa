#include <stdio.h> 
#include <algorithm>
using namespace std;

int main() {
	long long L, R, K;
	int cases = 0;
	while (scanf("%lld %lld %lld", &L, &R, &K) == 3 && L + R + K) {
		long long ret = 0, N = R - L;
//		for (int d = 1; d <= N; d++) {
//			if (K * (K-1) * d %2 == 0 && K * (K-1) * d / 2 % K == 0) {
//				int ra0 = R - (K-1) * d, la0 = L;
//				if (la0 <= ra0)
//					ret += ra0 - la0 + 1, printf("%d\n", ra0 - la0 + 1);
//				else
//					break;
//			}
//		}
		
		long long b0 = -1, bn = -1, bd = -1;
		for (long long d = 1; d <= N/(K-1); d++)  {
			if (K * (K-1) * d %2 == 0 && K * (K-1) * d / 2 % K == 0) {
				long long ra0 = R - (K-1) * d, la0 = L;
				if (la0 <= ra0) {
					if (b0 == -1)
						b0 = ra0 - la0 + 1;
					else {
						bd = b0 - (ra0 - la0 + 1);
						break;
					}
				}
			}
		}
		for (long long d = N / (K-1); d >= 1; d--)  {
			if (K * (K-1) * d %2 == 0 && K * (K-1) * d / 2 % K == 0) {
				long long ra0 = R - (K-1) * d, la0 = L;
				if (la0 <= ra0) {
					bn = ra0 - la0 + 1;
					break;
				}
			}
		}
		
		if (b0 != -1) {
			ret = (b0 + bn) * ((b0 - bn) / bd + 1)/2;
		}
//		printf("%lld %lld %lld\n", b0, bn, bd);
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
/*
1 20000000 10000000
1 20000000 100000
*/
