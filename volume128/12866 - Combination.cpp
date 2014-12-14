#include <stdio.h> 
// https://oeis.org/A006046
// a(0) = 0, a(1) = 1, a(2k) = 3*a(k), a(2k+1) = 2*a(k) + a(k+1).
long long f(long long n) {
	if (n < 2)	return n;
	if (n&1) 
		return f(n/2) * 2 + f(n/2 + 1);
	else
		return f(n/2) * 3;
}

unsigned long long dp[50] = {};
unsigned long long g(long long n) {
	if (n == 0)	return 0;
	if (n == 1)	return 1;
	if (n == 2)	return 3;
	if (n == 3)	return 5;
	if (n == 4)	return 9;
	if (n == 5)	return 11;
	if (n == 6)	return 15;
	if (n == 7)	return 19;
	long long i, j;
	for (i = 1, j = 1; 8 * i < n; i <<= 1, j++);
//	printf("%lld %lld %lld %lld\n", j, n, i, n - 4 * i);
	return dp[j] + 2 * g(n - 4 * i);
}
int main() {
	dp[1] = 9, dp[2] = 27;
	for (int i = 3; i < 50; i++)
		dp[i] = dp[i - 1] * 3;
	 
//	int C[105][105] = {}, totsum = 0;
//	C[0][0] = 1;
//	for (int i = 0; i < 100; i++) {
//		C[i][0] = 1;
//		int sum = 1;
//		for (int j = 1; j <= i; j++) {
//			C[i][j] = (C[i-1][j] + C[i-1][j-1])&1;
//			sum += C[i][j];
//		}
//		totsum += sum;
//		printf("%2d: %5d %5d\n", i, sum, totsum);
//	}
//	for (int i = 0; i < 50; i++) {
//		for (int j = 0; j <= i; j++)
//			printf("%d", C[i][j]);
//		puts("");
//	}
	long long L, R;
	while (scanf("%lld %lld", &L, &R) == 2) {
		if (L == 0 && R == 0)
			break;
//		printf("%lld %lld\n", f(R + 1), g(R + 1));
//		long long ret = f(R + 1) - f(L);
//		printf("%lld\n", ret);
		unsigned long long ret2 = g(R + 1) - g(L);
		printf("%llu\n", ret2);
	}
	return 0;
}
