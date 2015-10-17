#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main() {
	char s[128], abb[128], *ptr = abb;
	while (scanf("%s", s) == 1) {
		int n = strlen(s), end = 0;
		if (s[n-1] == '.') {
			end = 1, s[n-1] = '\0';
		}

		if (!strcmp(s, "of"));
		else if (!strcmp(s, "and"));
		else if (!strcmp(s, "the"));
		else if (!strcmp(s, "at"));
		else
			*ptr = toupper(s[0]), ptr++;		
		if (end == 1) {
			*ptr = '\0';
			puts(abb), ptr = abb;
			continue;
		}
	}
	return 0;
}
