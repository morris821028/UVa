#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int A[20], B[20], C[20];
long long dp[1<<16][5];
int used[1<<16][5] = {};
int cases = 0, n, m;
int getMask() {
	int ret = 0;
	for(int i = 0; i < m; i++)
		ret += C[i] * B[i];
	return ret;
}
long long dfs(int mod) {
	int mask = getMask();
	if(mask == 0)
		return mod == 0;
	if(used[mask][mod] == cases)
		return dp[mask][mod];
	used[mask][mod] = cases;
	long long &ret = dp[mask][mod];
	ret = 0;
	for(int i = 0; i < m; i++) {
		if(B[i]) {
			B[i]--;
			ret += dfs((mod * 16 + A[i])%5);
			B[i]++;
		}
	}
	if(mod == 0)	ret++;
	return ret;
}
int main() {
	char s[105];
	while(scanf("%s", s) == 1 && s[0] != '#') {
		n = strlen(s);
		sort(s, s + n);
		int i, j, prev = -1;
		m = 0;
		for(i = 0; i < n; i++) {
			int num;
			if(s[i] >= '0' && s[i] <= '9')
				num = s[i] - '0';
			else
				num = s[i] - 'A' + 10;
			if(num != prev) {
				A[m] = num, B[m] = 0, m++;
				prev = num;
			}
			B[m-1]++;
		}
		C[m-1] = 1;
		for(i = m-2; i >= 0; i--)
			C[i] = C[i+1] * (B[i+1] + 1);
		cases++;
		printf("%lld\n", dfs(0) - 1);
	}
	return 0;
}
