#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;

int dp[1<<20];

int pick(int state, int x) {
	for (int i = x; i <= 20; i += x)
		if ((state>>(i-2))&1)
			state ^= 1<<(i-2);
	
	for (int i = x; i <= 20; i++) {
		if ((state>>(i-2))&1) {
			if (i - x >= 2) {
				if (((state>>(i - x -2))&1) == 0)
					state ^= 1<<(i-2);
			}
		}
	}
	return state;
}
int dfs(int state) {
	if (state == 0)	
		return 0;
	if (dp[state] != -1)	
		return dp[state];
	int &ret = dp[state];
	ret = 0;
	for (int i = 2; i <= 20; i++) {
		if ((state>>(i-2))&1) {
			int v = dfs(pick(state, i));
			ret |= !v;
			if (ret) break;
		}
	}
	return ret;
}
int main() {
	memset(dp, -1, sizeof(dp));
	int testcase, cases = 0;
	int n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		int mask = 0, x;
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			mask |= 1<<(x-2);
		}
		
		printf("Scenario #%d:\n", ++cases);
		vector<int> ret;
		for (int i = 2; i <= 20; i++) {
			if ((mask>>(i-2))&1) {
				int v = dfs(pick(mask, i));
				if (v == 0)
					ret.push_back(i);
			}
		}
		if (ret.size() == 0)
			puts("There is no winning move.");
		else {
			printf("The winning moves are:");
			for (int i = 0; i < ret.size(); i++)
				printf(" %d", ret[i]);
			puts(".");
		}
		puts("");
	}
	return 0;
}
