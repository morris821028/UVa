#include <bits/stdc++.h>
using namespace std;

const int MAXS = 128;
char sa[MAXS], sb[MAXS];
int main() {
	int testcase, n, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %s %s", &n, sa, sb);
		int ret = 0;
		for (int i = 0; i < n; i++) {
			int a = sa[i] - '0';
			int b = sb[i] - '0';
			ret += min(abs(a-b), 10 - abs(a-b));
		}
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}

