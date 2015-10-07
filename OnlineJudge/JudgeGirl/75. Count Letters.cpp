#include <stdio.h>
#include <ctype.h>

int main() {
	char s[1024];
	while (gets(s)) {
		int cnt[128] = {};
		for (int i = 0; s[i]; i++)
			cnt[tolower(s[i])]++;
		for (int i = 'a'; i <= 'z'; i++)
			printf("%d\n", cnt[i]);
	}
	return 0;
}

