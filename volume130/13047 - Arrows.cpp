#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	char s[1024];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s", s);
		int n = strlen(s);
		int ret = -1;
		for (int i = 0; i < n; i++) {
			if (s[i] == '>') {
				int type = i ? s[i-1] : 0, cnt = 1;
				if (type == '=' || type == '-')
				for (int j = i-1; j >= 0 && s[j] == type; j--)
					cnt++;
				ret = max(ret, cnt);
			} else if (s[i] == '<') {
				int type = s[i+1], cnt = 1;
				if (type == '=' || type == '-')
				for (int j = i+1; s[j] && s[j] == type; j++)
					cnt++;
				ret = max(ret, cnt);
			}
		}
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}

