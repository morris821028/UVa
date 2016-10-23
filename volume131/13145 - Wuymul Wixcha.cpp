#include <bits/stdc++.h>
using namespace std;

int main() {
	int d;
	char s[65536];
	while (scanf("%d", &d) == 1 && d) {
		while (getchar() != '\n');
		fgets(s, 65536, stdin);
		d = (d%26 + 26)%26;
		for (int i = 0; s[i]; i++) {
			if (s[i] >= 'A' && s[i] <= 'Z') {
				s[i] = ((int)s[i]-'A'+d)%26 + 'A';
			} else if (s[i] >= 'a' && s[i] <= 'z') {
				s[i] = ((int)s[i]-'a'+d)%26 + 'a';
			}
		}
		fputs(s, stdout);
	}
	return 0;
}

