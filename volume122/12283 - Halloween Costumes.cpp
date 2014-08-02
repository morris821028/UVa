#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
 
int dp[105][105], a[105];
int dfs(int l, int r) {
	if(l > r)	return 0;
	int &ret = dp[l][r];
	if(ret != -1)	return ret;
	ret = min(dfs(l+1, r), dfs(l, r-1))+1;
	for(int i = l+1; i <= r; i++) {
		if(a[l] == a[i])
			ret = min(ret, dfs(l+1, i) + dfs(i+1, r));
	}
	return ret;
}
int main() {
	int cases = 0, testcase, n, m;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &n, &m);
		for(int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		memset(dp, -1, sizeof(dp));
		printf("Case %d: %d\n", ++cases, dfs(0, n-1));
	}
	return 0;
}
/*
4 

1 1 
1 

2 2 
1 1 

3 2 
1 2 1 

7 3 
1 2 1 1 3 2 1
*/
