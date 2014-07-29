#include <stdio.h>
#include <map>
#include <algorithm>
using namespace std;

int main() {
	int n, cases = 0;
	int a, b;
	while(scanf("%d", &n) == 1 && n) {
		map<int, int> R[1024];
		for(int i = 0; i < n; i++) {
			scanf("%d %d", &a, &b);
			if(a + b >= n)
				continue;
			int &ww = R[a+1][n-b];
			ww = min(ww + 1, n - a - b);
		}
		int ret = 0, dp[1024] = {};
		for(int i = 0; i <= n; i++) {
			if(i)
				dp[i] = max(dp[i], dp[i-1]);
			for(map<int, int>::iterator it = R[i+1].begin();
				it != R[i+1].end(); it++)
				dp[it->first] = max(dp[it->first], dp[i] + it->second);
			ret = max(ret, dp[i]);
		}
		printf("Case %d: %d\n", ++cases, n - ret);
	}
	return 0;
}
