#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m;
	char s[1024];
	while (scanf("%s %d", s, &m) == 2 && m) {
		if (s[0] == '0' && s[1] == 'x')
			sscanf(s, "%X", &n);
		else if (s[0] == '0')
			sscanf(s, "%o", &n);
		else
			sscanf(s, "%d", &n);
		int ret = 0, val;
		for (int i = 0; i < m; i++) {
			char cmd[16];
			scanf("%s %d", cmd, &val);
			if (!strcmp(cmd, "i")) {
				ret += val == n;
				if (val != n)
					n = val;
			} else if (!strcmp(cmd, "i++")) {
				ret += val == n;
				if (val != n)
					n = val;
				n++;
			} else if (!strcmp(cmd, "i--")) {
				ret += val == n;
				if (val != n)
					n = val;
				n--;
			} else if (!strcmp(cmd, "++i")) {
				++n;
				ret += val == n;
				if (val != n)
					n = val;
			} else if (!strcmp(cmd, "--i")) {
				--n;
				ret += val == n;
				if (val != n)
					n = val;
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}

