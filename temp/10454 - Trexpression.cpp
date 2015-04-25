#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;

const int MAXN = 256;
long long dp[MAXN][MAXN];
char s[MAXN];

long long dfs(int l, int r) {
	if (l == r)			return 1;
	if (dp[l][r] != -1)	return dp[l][r];
	long long &ret = dp[l][r];
	ret = 0;
	int left = 0, o1 = 0, o2 = 0;
	for (int i = l; i <= r; i++) {
		if (s[i] == '(')
			left++;
		else if (s[i] == ')')
			left--;
		else {
			if (left == 0) {
				if (s[i] == '+')	
					o1 = 1;
				if (s[i] == '*')
					o2 = 1;
			}				
		}
	}
	if (o1 == 0 && o2 == 0)
		ret += dfs(l+1, r-1);
	for (int i = l; i <= r; i++) {
		if (s[i] == '(')
			left++;
		else if (s[i] == ')')
			left--;
		else {
			if (left == 0) {
				if (s[i] == '+')
					ret += dfs(l, i-1) * dfs(i+1, r);
				if (s[i] == '*' && o1 == 0)
					ret += dfs(l, i-1) * dfs(i+1, r);
			}				
		}
	}
	return ret;
}
int main() {
	while (gets(s)) {
		memset(dp, -1, sizeof(dp));
		long long v = dfs(0, strlen(s) - 1);
		printf("%lld\n", v);
	}
	return 0;
}
