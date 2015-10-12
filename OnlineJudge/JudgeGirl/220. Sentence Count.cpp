#include <stdio.h>
#include <ctype.h>
char buf[1<<20] = {};
int main() {
	fread(buf, 1, 1<<20, stdin);
	int ret = 0;
	for (int i = 0; buf[i]; i++) {
		if (buf[i] == '.') {
			if (buf[i+1] == ' ' && buf[i+2] == ' ')
				ret++;
			else if (buf[i+1] == '\n' || buf[i+1] == '\0')
				ret++;
		}
	}
	printf("%d\n", ret);
	return 0;
}
