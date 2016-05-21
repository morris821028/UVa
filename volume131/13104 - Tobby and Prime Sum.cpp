#include <bits/stdc++.h>
using namespace std;
#define MAXL (50000>>5)+1
#define GET1(x) (mark1[(x)>>5]>>((x)&31)&1)
#define SET1(x) (mark1[(x)>>5] |= 1<<((x)&31))
int mark1[MAXL];
int P[5500], Pt = 0;
const int MOD = 1e9+7;
void sieve() {
    register int i, j, k;
    SET1(1), SET1(0);
    int n = 50000;
    for (i = 2; i <= n; i++) {
        if (!GET1(i)) {
            for (k = n/i, j = i*k; k >= i; k--, j -= i)
                SET1(j);
            P[Pt++] = i;
        }
    }
}
int dp[512][10];
int dp_sum[512][10][5015];
void build() {
	int f[2][5015] = {};
	int p = 0, q = 1;
	f[0][0] = 1, dp_sum[0][0][0] = 1;
	for (int i = 0; i < 500; i++) {
		memset(f[q], 0, sizeof(f[0]));
		for (int k = 0; k <= i * 10; k++) {
			if (!f[p][k])	continue;
			for (int r = 0; r < 10; r++) {
				f[q][k+r] += f[p][k];
				if (f[q][k+r] >= MOD)
					f[q][k+r] -= MOD;
				dp_sum[i+1][r][k+r] += f[p][k];
				if (dp_sum[i+1][r][k+r] >= MOD)
					dp_sum[i+1][r][k+r] -= MOD;
				if (!GET1(k+r)) {
					dp[i+1][r] += f[p][k];
					if (dp[i+1][r] >= MOD)
						dp[i+1][r] -= MOD;
				}
			}
		}
		p ^= 1, q ^= 1;
	}
//	for (int i = 1; i <= 2; i++) {
//		for (int j = 0; j < 10; j++)
//			printf("%d ", dp[i][j]);
//		puts("");
//	}
}

long long f(char s[]) {
	int n = strlen(s);
	long long ret = 0;
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < 10; j++) {
			ret += dp[i][j];
			if (ret >= MOD)
				ret -= MOD;
		}
	}
//	printf("%d\n", GET1(8));
//	printf("--- %lld\n", ret);
	long long base = 0, pre = 0, sum = 0;
	for (int i = 0; i < n; i++) {
		int d = s[i] - '0';
		for (int j = (i == 0); j < d; j++) {
			for (int k = 0; k <= (n-i)*10; k++) {
				if (GET1((k+sum)) == 0) {
					if (dp_sum[n-i][j][k] == 0)	
						continue;
//					printf("digits %d, head %d, sum %d, %lld %d\n",n-i, j, k, pre - base + 1, dp_sum[n-i][j][k]);
					ret = (ret + (pre - base + 1) * dp_sum[n-i][j][k] % MOD)%MOD;
				}
			}
		}
		pre = pre * 10 + d;
		pre %= MOD;
		base = base * 10 + d;
		base %= MOD;
		sum += d;
	}
	if (!GET1(sum))
		ret++;
	ret = ret % MOD;
	return ret;
}
int main() {
	sieve();
	build();
	char s1[1024], s2[1024];
	while (scanf("%s %s", s1, s2) == 2) {
		int sum = 0;
		for (int i = 0; s1[i]; i++)
			sum += s1[i] - '0';
		long long ret = f(s2) - f(s1) + (GET1(sum) == 0);
		ret = (ret%MOD + MOD)%MOD;
		printf("%lld\n", ret);
	}
	return 0;
}
/*
1  10
20  46

4 
11
*/

