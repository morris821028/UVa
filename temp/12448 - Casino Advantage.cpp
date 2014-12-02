#include <stdio.h> 
#include <algorithm>
using namespace std;

long long gcd(long long x, long long y) {
	long long t;
	while (x%y)
		t = x, x = y, y = t%y;
	return y;
}
int main() {
	int testcase;
	int N, M, K;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d", &N, &M, &K);
		long long dp[16][16] = {};
		long long a = 0, b = 1, g;		
		dp[0][0] = 1;
		for (int i = 1; i <= M; i++) {
			for (int j = 1; j <= min(i, K); j++) {
				dp[i][j] = dp[i-1][j] * j + dp[i-1][j-1] * (N - (j-1));
			}
			b *= N;
		}
		a = dp[M][K];
		g = gcd(a, b);
		a /= g, b /= g;
		if (a%b == 0)	printf("%lld\n", a/b);
		else			printf("%lld/%lld\n", a, b);
	}
	return 0;
}
