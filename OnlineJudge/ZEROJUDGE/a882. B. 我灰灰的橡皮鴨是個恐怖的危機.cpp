#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	char s[32767];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s", s);
		int ret = 0;
		for (int i = 0; s[i]; i++) {
			if (s[i] == 'X')
				ret += 2;
			else if (s[i] == 'H')
				ret += 1;
		}
		printf("%d\n", ret);
	} 
	return 0;
}
