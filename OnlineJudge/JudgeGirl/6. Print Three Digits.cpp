#include <stdio.h>

int main() {
	char s[20];
	while(scanf("%s", s) == 1)
		printf("%c\n%c\n%c\n", s[0], s[1], s[2]);
	return 0;	
}

