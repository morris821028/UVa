#include <bits/stdc++.h> 
using namespace std;

const int64_t MOD = 1000000009;
const int MAXN = 520;
const int MAXK = 9;
int64_t C[MAXN][MAXN];
int64_t P[MAXK][MAXN][MAXN];
// P[k-ary][depth-1][depth-2]

void build() {
	C[0][0] = 1;
	for (int i = 1; i < MAXN; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			C[i][j] = C[i-1][j-1] + C[i-1][j];
			if (C[i][j] >= MOD)
				C[i][j] -= MOD;
		}
	}
	memset(P, -1, sizeof(P));
}
int64_t p(int a, int b, int k) {
	if (b == 0)	return 1;
	if (a == 0)	return 0;
	int64_t &ret = P[k][a][b];
	if (ret != -1)
		return ret;
	int64_t tmp = 0;
	int g = min(b, k);
	for (int i = 0; i <= g; i++) {
		tmp = tmp + C[b][i]*p(a-1, b-i, k);
		if (tmp >= MOD)
			tmp %= MOD;
	}
	return ret = tmp;
}
int main() {
	build();
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int d, k, c, c_pre;
		scanf("%d %d", &d, &k);
		scanf("%d", &c_pre);
		int64_t ret = 1;
		for (int i = 0; i < d; i++) {
			scanf("%d", &c);
			ret = ret * p(c_pre, c, k);
			if (ret >= MOD)
				ret %= MOD;
			c_pre = c;
		}
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
/*
2
2 3
1 3 2
8 8
1 4 10 14 17 24 26 26 30
*/
