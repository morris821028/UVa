#include <bits/stdc++.h>
using namespace std;

int main() {
	static char s[524288];
	while (scanf("%s", s) == 1) {
		int ret = 0, prev = -1, n = strlen(s);
		for (int i = 0; i < n; i++) {
			if (s[i] == 'X') {
				if (prev == -1) {
					ret = max(ret, i-1);
					prev = i;
				} else {
					ret = max(ret, (i-prev-2)/2);
					prev = i;
				}
			}
		}
		if (prev != n-1)
			ret = max(ret, n-prev-2);
		printf("%d\n", ret);
	}
	return 0;
}

