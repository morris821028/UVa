#include <bits/stdc++.h> 
using namespace std;

int main() {
	int n;
	char s[16];
	while (scanf("%d", &n) == 1) {
		int next[8] = {};
		for (int i = 0; i < 6; i++) {
			scanf("%s", s);
			int st = s[0]-'A'+1;
			int ed = s[1]-'A'+1;
			if (next[st] == 0)
				next[st] = ed;
		}
		
		int a, b;
		if (next[2] != 1 && next[3] != 1) {
			// A -> B -> C -> B -> C ...
			// or A -> C -> B -> C -> B ...
			a = 3, b = 0;
		} else if (next[next[1]] == 1) {
			a = 3, b = 2;
		} else {
			a = 2, b = 1;
		}
		
		int64_t dp[64] = {};
		dp[1] = 1;
		for (int i = 2; i <= n; i++)
			dp[i] = dp[i-1]*a + b;
		printf("%lld\n", dp[n]);
	}
	return 0;
}
/*
3
AB BC CA BA CB AC
2
AB BA CA BC CB AC
*/
