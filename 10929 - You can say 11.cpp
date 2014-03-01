#include <stdio.h>
#include <string.h>
int main() {
	char s[1001];
	while(scanf("%s", s) == 1) {
		if(strcmp(s, "0") == 0)
			break;
		int i, l = strlen(s), sum = 0;
		for(i = l-1; i >= 0; i -= 2)
			sum += s[i] - '0';
		for(i = l-2; i >= 0; i -= 2)
			sum -= s[i] - '0';
		printf("%s ", s);
		if(sum%11 == 0) 
			puts("is a multiple of 11.");
		else
			puts("is not a multiple of 11.");
	}
    return 0;
}
