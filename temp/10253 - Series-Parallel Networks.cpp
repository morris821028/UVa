#include <stdio.h> 
#include <algorithm>
using namespace std;

long long dp[32][32] = {};
/*
parallel/series
consider parallel/series operation -> node, 
n-edge == counting number of tree with n-leaf node.

dp[i][j]: at most i-leaves in subtree, total j-leaves.
dp[i][j] = \sum C(ret[i] + k - 1, k) \times dp[i-1][j - i*k]
				^^^^^^^^^^^^^^^^^^^^[1]		^^^^^^^^^^^^^^^[2]
[1]: pick k subtree with at most (i-1)-leaves, total i-leaves
[2]: a subtree with at most (i-1)-leaves, total (j-i*k)-leaves
*/
long long C(long long n, long long m) {
	long long ret = 1;
	m = min(m, n-m);
	for (long long i = 1; i <= m; i++)
		ret = ret * (n + 1 - i) / i;
	return ret;
}
int main() {
	
	long long ret[32] = {};
	ret[1] = 1;
	for (int i = 1; i <= 30; i++)
		dp[0][i] = 0, dp[i][1] = 1;
	for (int i = 0; i <= 30; i++)
		dp[i][0] = 1;
	for (int i = 1; i <= 30; i++) {
		for (int j = 2; j <= 30; j++) {
			for (int k = 0; i * k <= j; k++) {
				dp[i][j] += C(ret[i] + k - 1, k) * dp[i-1][j - i*k];
			}
		}
		ret[i+1] = dp[i][i+1];
	}
	
	int n;
	while (scanf("%d", &n) == 1 && n)
		printf("%lld\n", n == 1 ? 1 : ret[n] * 2);
	return 0;
}
