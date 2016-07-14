#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (getchar() != '\n');
	while (testcase--) {
		static char s[131072];
//		scanf("%s", s);
		fgets(s, 131072, stdin);
		int cnt[128] = {};
		for (int i = 0; s[i] > ' '; i++)
			cnt[s[i]]++;
		int mn = INT_MAX;
		for (int i = 'a'; i <= 'z'; i++)
			mn = min(mn, cnt[i]);
		printf("Case %d: %d\n", ++cases, mn);
	}
	return 0;
}
/*
2
ab
efzadeuopqxrvwxaghijklmnbcastbqy
*/
