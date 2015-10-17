#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char buf[262144], s[128];
	int n, m;
	scanf("%s", buf);
	n = strlen(buf);
	while (scanf("%s", s) == 1) {
		m = strlen(s);
		int overlap = 0;
		for (int i = m < n ? m : n; i >= 1; i--) {
			int ok = 1;
			for (int j = 0, k = n-i; j < i && ok; j++, k++)
				ok &= buf[k] == s[j];
			if (ok) {
				overlap = i;
				break;
			}
		}
		for (int i = overlap; i < m; i++)
			buf[n++] = s[i];
		buf[n] = '\0';
	}
	puts(buf);
	return 0;
}

