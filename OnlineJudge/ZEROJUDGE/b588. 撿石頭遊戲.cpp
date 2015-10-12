#include <bits/stdc++.h>
using namespace std;
char dp[128][128][128] = {};
int dfs(int x, int y, int z) {
	int v[] = {x, y, z};
	sort(v, v+3);
	int a = v[0], b = v[1], c = v[2];
	if (a == 0 && b == 0 && c == 0)
		return 0;
	if (dp[a][b][c] != -1)	return dp[a][b][c];
	char &f = dp[a][b][c];
	f = 0;
	for (int i = a; i >= 1 && !f; i--)
		f |= !dfs(a-i, b, c);
	for (int i = b; i >= 1 && !f; i--)
		f |= !dfs(a, b-i, c);
	for (int i = c; i >= 1 && !f; i--)
		f |= !dfs(a, b, c-i);
	for (int i = min(a, b); i >= 1 && !f; i--)
		f |= !dfs(a-i, b-i, c);
	for (int i = min(a, c); i >= 1 && !f; i--)
		f |= !dfs(a-i, b, c-i);
	for (int i = min(b, c); i >= 1 && !f; i--)
		f |= !dfs(a, b-i, c-i);
	for (int i = min(min(b, c), a); i >= 1 && !f; i--)
		f |= !dfs(a-i, b-i, c-i);
	return f;
}
int main() {
	memset(dp, -1, sizeof(dp));
	int x, y, z;
	while (scanf("%d %d %d", &x, &y, &z) == 3) {
		int ret = dfs(x, y, z);
		puts(ret ? "w" : "l");
	}
	return 0;
}
