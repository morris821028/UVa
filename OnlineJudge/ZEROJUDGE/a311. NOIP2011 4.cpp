#include <bits/stdc++.h>
using namespace std;
const int mod = 10007;
char s[131072];
pair<int, int> dfs(int l, int r) {
	if (l == r+1)
		return {1, 1};
	for (int i = l, a = 0; i <= r; i++) {
		if (s[i] == '(')		a++;
		else if (s[i] == ')')	a--;
		else {
			if (a == 0 && s[i] == '+') {
				pair<int, int> L, R, V;
				L = dfs(l, i-1), R = dfs(i+1, r);
				V.first = (L.first*R.first)%mod;
				V.second = (((L.first+L.second)*(R.first+R.second)%mod - V.first)%mod + mod)%mod;
				return V;
			}
		}
	}
	for (int i = l, a = 0; i <= r; i++) {
		if (s[i] == '(')		a++;
		else if (s[i] == ')')	a--;
		else {
			if (a == 0 && s[i] == '*') {
				pair<int, int> L, R, V;
				L = dfs(l, i-1), R = dfs(i+1, r);
				V.second = (L.second*R.second)%mod;
				V.first = (((L.first+L.second)*(R.first+R.second)%mod - V.second)%mod + mod)%mod;
				return V;
			}
		}
	}
	return dfs(l+1, r-1);
}
int main() {
	int L;
	while (scanf("%d %s", &L, s) == 2) {
		pair<int, int> ret = dfs(0, L-1);
		printf("%d\n", ret.first);
	}
	return 0;
}
/*
4
+(*)
*/

