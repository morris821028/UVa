#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	char s[1024];
	while (scanf("%d", &n) == 1) {
		scanf("%s", s);
		
		int same = 1;
		for (int i = 1; i < n; i++)
			same &= s[i] == s[0];
		if (same) {
			printf("%d\n", n);
			continue;
		}
		
		for (int i = 0; i < n; i++)
			s[n+i] = s[i];
		int ret = 0;
		for (int i = 1; i < 2*n; i++) {
			int l = i, s1 = 0, s2 = 0;
			int deter = 0, c = -1;
			while (l < 2*n) {
				if (deter && s[l] != c && s[l] != 'w')
					break;
				if (s[l] != 'w' && deter == 0)
					deter = 1, c = s[l];
				l++, s1++;
			}
			l = i-1, deter = 0, c = -1;
			while (l >= 0) {
				if (deter && s[l] != c && s[l] != 'w')
					break;
				if (s[l] != 'w' && deter == 0)
					deter = 1, c = s[l];
				l--, s2++;
			}
			ret = min(max(ret, s1 + s2), n);
		}
		printf("%d\n", ret);
	}
	return 0;
} 
