#include <stdio.h>
#include <ctype.h>
int main() {
	char s[1024];
	while (fgets(s, 1024, stdin)) {
		int v[4] = {};
		for (int i = 0; s[i]; i++) {
			if (isdigit(s[i]))
				v[0]++;
			else if (isalpha(s[i])) {
				v[1]++;
				s[i] = tolower(s[i]);
				if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i'
					|| s[i] == 'o' || s[i] == 'u')
					v[2]++;
				else
					v[3]++;
			}
		}
		printf("%d %d %d %d\n", v[0], v[1], v[2], v[3]);
	}
	return 0;
}
