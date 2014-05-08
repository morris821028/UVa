#include <stdio.h>
#include <stack>
using namespace std;
int main() {
	for(int n; scanf("%d", &n) == 1;) {
		int a[15], b[15], c[15], dp[2400] = {}, best[2400] = {};
		char s[15][15];
		for(int i = 0; i < n; i++) {
			scanf("%s %d %d %d", s[i], &a[i], &b[i], &c[i]);
		}
		int ret = 0, end;
		for(int i = 0; i < 2400; i++) {
			if(dp[i] <= dp[i-1] && i)
				best[i] = -1, dp[i] = dp[i-1];
			for(int j = 0; j < n; j++) {
				if(a[j] == i) {
					if(dp[b[j]] <= dp[i] + c[j])
						dp[b[j]] = dp[i] + c[j], best[b[j]] = j;
				}				
			}
			if(dp[i] > ret)
				ret = dp[i], end = i;
		}
		stack<int> stk;
		for(int i = end; i; ) {
			if(best[i] == -1)
				i--;
			else
				stk.push(best[i]), i = a[best[i]];
		}
		while(!stk.empty())
			printf("%s ", s[stk.top()]), stk.pop();
		printf("%d\n", ret);
	}
	return 0;
}
