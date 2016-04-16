#include <bits/stdc++.h>
using namespace std;

string dfs(int n, string s) {
	if (n == 0)	return "";
	char mx = s[0];
	for (int i = 0; i < n; i++)
		mx = max(mx, s[i]);
	for (int i = n-1; i >= 0; i--) {
		if (s[i] == mx) {
			string mm = string(1, mx);
			return mm + dfs(i, s.substr(0, i)) + s.substr(i+1) ;
		}
	}
	return "";
}
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		char cs[1024];
		scanf("%s", cs);
		int n = strlen(cs);
		string v = dfs(n, cs);
		printf("Case #%d: %s\n", ++cases, v.c_str());
	}
	return 0;
}

