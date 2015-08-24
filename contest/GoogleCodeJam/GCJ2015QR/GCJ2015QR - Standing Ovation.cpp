#include <stdio.h>
#include <algorithm>
using namespace std;

const int MAXN = 1024;
char s[MAXN];
int main() {
	int testcase, cases = 0, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %s", &n, s);
		
		int ret = 0, p = 0;
		for (int i = 0; i <= n; i++) {
			if (i > p && s[i] - '0') {
				int need = i - p;
				ret += need;
				p += need;
			}
			p += s[i] - '0';
		}
		printf("Case #%d: %d\n", ++cases, ret);
	}
	return 0;
}
