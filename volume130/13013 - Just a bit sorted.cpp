#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5005;
const long long MOD = 1e9+7;
long long dp[MAXN][MAXN], sum[MAXN][MAXN];

// [2, 3, 1, 2] is a valid sequence.
// L(i): set of number i appear position
// L(1) = {3}, L(2) = {1, 4}, L(3) = {2}
// concatenate L(K)L(K-1)...L(1) = [2, 1, 4, 3]
// map to Euler's Triangle
// find n elements sequence, k places where A(i) > A(i+1)
// E(n, k) = (k+1) E(n-1, k) + (n-k) E(n-1, k-1)
// Reference. Textbook: Concrete Mathematics page. 268 
int main() {
	dp[0][0] = 1;
	for (int i = 1; i < MAXN; i++) {
		dp[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			dp[i][j] = (j+1)*dp[i-1][j]+(i-j)*dp[i-1][j-1];
			dp[i][j] %= MOD;
		}
	}
	
	for (int i = 0; i < MAXN; i++) {
		long long t = 0;
		for (int j = 0; j <= i; j++) {
			t += dp[i][j];
			t %= MOD;
			sum[i][j] = t;
		}
	} 
	int N, Q, K;
	while (scanf("%d %d", &N, &Q) == 2) {
		vector<long long> ret;
		for (int i = 0; i < Q; i++) {
			scanf("%d", &K);
			K = min(K, N);
			ret.push_back(sum[N][K-1]);
		}
		for (int i = 0; i < ret.size(); i++) {
			if (i)	putchar(' ');
			printf("%lld", ret[i]);
		}
		puts("");
	}
	return 0;
}

