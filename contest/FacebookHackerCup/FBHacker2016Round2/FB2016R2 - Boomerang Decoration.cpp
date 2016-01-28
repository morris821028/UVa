#include <bits/stdc++.h>
using namespace std;

const int MAXS = 131072;
char sa[MAXS], sb[MAXS];
int Ldp[MAXS], Rdp[MAXS];
int main() {
	int testcase, cases = 0;
	int n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		scanf("%s %s", sa+1, sb+1);
		
		memset(Ldp, 0, sizeof(Ldp));
		memset(Rdp, 0, sizeof(Rdp));
		
		int c;
		c = 0;
		for (int i = 1; i <= n; i++) {
			if (sb[i] != sb[i-1])
				c++;
			if (sa[i] != sb[i])
				Ldp[i] = c;
			else
				Ldp[i] = Ldp[i-1];
		}
		c = 0;
		for (int i = n, j = 1; i >= 1; i--, j++) {
			if (sb[i] != sb[i+1])
				c++;
			if (sa[i] != sb[i])
				Rdp[j] = c;
			else
				Rdp[j] = Rdp[j-1];
		}
		int ret = n;
		for (int i = 1; i <= n; i++) {
			ret = min(ret, max(Ldp[i], Rdp[n-i]));
		}
		printf("Case #%d: %d\n", ++cases, ret);
	}
	return 0;
}

