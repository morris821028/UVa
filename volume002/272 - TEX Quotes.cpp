#include<stdio.h>
int main() {
	char s[10001];
	int i, flag = 0;
	while(gets(s)) {
		for(i = 0; s[i]; i++) {
			if(s[i] == '\"') {
				if(!flag) {
					printf("``");
				} else
					printf("''");
				flag = 1 - flag;
			} else
				putchar(s[i]);
		}
		puts("");
	}
    return 0;
}
