#include <bits/stdc++.h>
using namespace std;
const int64_t MAXV = 1e+15;
const int MAXN = 32768;
int64_t P[32] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43,
				47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 91, 97};
int64_t ret[MAXN]= {};
void dfs(int64_t v, int fcnt, int idx, int prev) {
	int64_t lim = MAXV / v;
	if (ret[fcnt] == -1) {
		ret[fcnt] = v;
	} else {
		if (ret[fcnt] > v)
			ret[fcnt] = v;
	}
	for (int i = 1; i <= prev; i++) {
		lim /= P[idx], v *= P[idx];
		if (lim == 0)
			return ;
		dfs(v, fcnt*(i+1), idx+1, i);
	}
}
void build() {
	memset(ret, -1, sizeof(ret));
	ret[1] = 1;
	dfs(1, 1, 0, 64);
}
int main() {
	build();
	int n, cases = 0;
	while (scanf("%d", &n) == 1 && n) {
		printf("Case %d: ", ++cases);
		if (ret[n] == -1 || n >= MAXN)
			puts("Impossible");
		else
			printf("%lld\n", ret[n]);
	}
	return 0;
}
/*
60 = 4 * 3 * 5
*/
