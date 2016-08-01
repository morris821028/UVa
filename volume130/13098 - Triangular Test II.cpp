#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e+7 + 5;
unsigned char dp[MAXN];
int A[MAXN], An = 0;
int main() {
	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0;
	for (int i = 1, x = 1; x <= MAXN; i++, x += i)
		A[An++] = x;
	for (int i = 0; i < An; i++)
		dp[A[i]] = 1;
	for (int i = 0; i < An; i++) {
		for (int j = i; j < An && A[i]+A[j] <= MAXN; j++)
			dp[A[i]+A[j]] = min(dp[A[i]+A[j]], (unsigned char)2);
	}
	int n;
	while (scanf("%d", &n) == 1) {
		if (dp[n] <= 2)
			printf("%d\n", dp[n]);
		else
			puts("3");
	}
	return 0;
}

