#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1024;
char s[MAXN];
int dp[MAXN][MAXN], argdp[MAXN][MAXN];
int bidx = 0;
char buf[MAXN];
void dfs(int l, int r) {
	if (l > r)	return ;
	if (l == r) {
		buf[bidx++] = s[l];
		return;
	}
	if (argdp[l][r] == 0) {
		buf[bidx++] = s[l];
		dfs(l+1, r-1);
		buf[bidx++] = s[l];
	} else if (argdp[l][r] == 1) {
		dfs(l+1, r);
	} else {
		dfs(l, r-1);
	}
}
int main() {
	while (scanf("%s", s) == 1) {
		int n = strlen(s);
		for (int i = 0; i < n; i++)
			dp[i][i] = 1;
		for (int i = 1; i < n; i++) {
			for (int j = 0; j + i < n; j++) {
				int mx = 0, dir;
				if (s[j] == s[j+i]) {
					if (dp[j+1][j+i-1]+2 > mx)
						mx = dp[j+1][j+i-1]+2, dir = 0;
				}
				if (dp[j+1][j+i] > mx)
					mx = dp[j+1][j+i], dir = 1;
				if (dp[j][j+i-1] > mx)
					mx = dp[j][j+i-1], dir = 2;
				dp[j][j+i] = mx, argdp[j][j+i] = dir;
			}
		}
		bidx = 0;
		dfs(0, n-1);
		buf[bidx] = '\0';
		puts(buf);
	}
	return 0;
}

