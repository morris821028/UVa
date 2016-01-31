#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	char s[1024];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s", s);
		int n = strlen(s);
		int ret = 0;
		for (int i = 0; i < n; i++) {
			if (s[i] != '-')
				continue;
			int valid = 1;
			if (i+1 < n && s[i+1] == 'B')
				valid = 0;
			if (i+2 < n && s[i+2] == 'B')
				valid = 0;
			if (i+1 < n && s[i+1] == 'S')
				valid = 0;
			if (i-1 >= 0 && s[i-1] == 'S')
				valid = 0;
			if (valid)
				ret++;
		}
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}

