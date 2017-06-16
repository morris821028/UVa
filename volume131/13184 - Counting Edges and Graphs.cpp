#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = 1e9+7;

int main() {
	int mask[8192] = {};
	mask[1] = 1;
	for (int i = 2; i < 8192; i++) {
		if (mask[i] == 0) {
			mask[i] = 2;
			for (int j = i+i; j < 8192; j += i) {
				if (mask[j] == 0) {
					int n = j, cnt = 0;
					while (n%i == 0)
						n /= i, cnt++;
					mask[j] = mask[n]*(cnt+1);
				}
			}
		}
	}
	
	int C[128][128] = {};
	C[0][0] = 1;
	for (int i = 1; i < 128; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++)
			C[i][j] = (C[i-1][j-1] + C[i-1][j])%MOD;
	}
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int N, K;
		int64_t E = 0, W = 1;
		scanf("%d %d", &N, &K);
		for (int i = 1; i <= N; i++) {
			E = E + min(mask[i]-1, K);
			if (E >= MOD)	E -= MOD;
			if (mask[i]-1 > K) {
				W = W * C[mask[i]-1][K];
				if (W >= MOD)
					W %= MOD;
			}
		}
		printf("%lld %lld\n", E, W);
	}
	return 0;
}
