#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	char s[1024];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s", s);
		for (int i = 0; s[i]; i++)
			putchar(((s[i]-'A')+3)%26 + 'A');
		puts("");
	}
	return 0;
}