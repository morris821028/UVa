#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, x;
	while (scanf("%d", &n) == 1) {
		char s[60];
		for (int i = 0; i < n; i++)
			scanf("%d", &x), s[i] = x + '0';
		s[n] = '\0';
		sort(s, s + n);
		int ret = 0;
		do {
			int a, b, i = n/2;
			char tmp = s[i];
			sscanf(s+i, "%d", &b);
			s[i] = '\0';
			sscanf(s, "%d", &a);
			s[i] = tmp;
			ret = max(ret, a*b);
		} while (next_permutation(s, s+n));
		printf("%d\n", ret);
	}
	return 0;
}

