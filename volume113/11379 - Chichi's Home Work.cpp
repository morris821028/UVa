#include <bits/stdc++.h> 
using namespace std;

const int64_t MOD = 1000000000;
const int MAXN = 1005;
int64_t C[MAXN]; // catalan number
int64_t dp[MAXN][MAXN];
void build() {
	C[0] = C[1] = 1;
	for (int i = 2; i <= 1000; i++) {
		int64_t s = 0;
		for (int j = 0; j < i; j++) {
			s += C[j] * C[i-1-j];
			s %= MOD;
		}
		C[i] = s;
	}

	for (int i = 0; i < 1000; i++) {
		int64_t s = 0;
		for (int j = 0; j <= i; j++) {
			s += C[i-j] * C[j];
			s %= MOD;
			dp[i+1][j+1] = s;
		}
	}
}

int main() {
	build();
	int n, x, y;
	while (scanf("%d %d %d", &n, &x, &y) == 3) {
		int64_t ret = 0;
		for (int i = y; i <= n; i++) {
			ret += dp[n-(i-x)][x] * C[i-x];
			ret %= MOD;
		}
		printf("%lld\n", ret);
	}
	return 0;
}
/*
6 2 4
500 35 67
*/
