#include <stdio.h>
#include <string.h>
int main() {
	char s[1001];
	while(scanf("%s", s) == 1) {
		if(strcmp(s, "0") == 0)
			break;
		int i, sum = 0;
		for(i = 0; s[i]; i++)
			sum += s[i]-'0';
		printf("%s is ", s);
		if(sum%9 != 0)
			puts("not a multiple of 9.");
		else {
			int degree = 1;
			while(sum >= 10) {
				sprintf(s, "%d", sum);
				sum = 0;
				for(i = 0; s[i]; i++)
					sum += s[i]-'0';
				degree++;
			}
			printf("a multiple of 9 and has 9-degree %d.\n", degree);
		}
	}
    return 0;
}
