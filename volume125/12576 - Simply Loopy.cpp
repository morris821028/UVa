#include <bits/stdc++.h> 
using namespace std;
const int MOD = 7477777;
const int MAXN = 100005;
int sq[MAXN], C[MAXN];
int main() {
	for (int i = 1; i < MAXN; i++) {
		sq[i] = ((int64_t) i*i)%MOD;
		C[i] = (int64_t) i*(i-1)*(i-2)/6%MOD;
	}
		
	int testcase, cases = 0;
	int n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		int64_t ret = 0;
		for (int i = 1; i <= n-4; i++)
			ret = ((int64_t) sq[i]*C[n-i-1] + ret)%MOD;
		ret = (ret*5)%MOD;
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
