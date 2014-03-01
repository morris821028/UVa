#include <stdio.h>
#include <string.h>
int main() {
	int n, l;
	char s[10000];
	scanf("%d", &n);
	while(n--) {
		scanf("%s", s);
		l = strlen(s);
		if(s[l-1] == '5')
			puts("-");
		else if(s[0] == '9' && s[l-1] == '4')
			puts("*");
		else if(s[0] == '1' && l >= 3)
			puts("?");
		else
			puts("+");
	}
    return 0;
}
