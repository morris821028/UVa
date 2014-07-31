#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <functional>
using namespace std;
int n;
long long A[32], suffix[32], ret;
void dfs(int i, long long x, long long y, long long sold) {
	if(sold >= ret || abs(x - y) > suffix[i])	return;
	if(x == y)
		ret = min(ret, sold + suffix[i]);
	if(i == n)
		return;
	if(x == y) {
		dfs(i+1, x + A[i], y, sold);
		dfs(i+1, x, y, sold + A[i]);
	} else {
		dfs(i+1, x + A[i], y, sold);
		if(x)
			dfs(i+1, x, y + A[i], sold);
		dfs(i+1, x, y, sold + A[i]);
	}
}
int main() {
	while(scanf("%d", &n) == 1 && n) {
		for(int i = 0; i < n; i++)
			scanf("%lld", &A[i]);
		sort(A, A+n, greater<long long>());
		suffix[n] = 0;
		for(int i = n-1; i >= 0; i--)
			suffix[i] = suffix[i+1] + A[i];
		ret = 1LL<<60;
		dfs(0, 0, 0, 0);
		printf("%lld\n", ret);
	}
	return 0;
}
