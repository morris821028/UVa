#include<stdio.h>
main() {
	char s[1001];
	while(gets(s)) {
		int a, flag = 0;
		for(a = 0; s[a]; a++) {
			if(s[a] >= 'a' && s[a] <= 'z') {
				if(flag) {
					if(s[a] == 'i' && !(s[a+1] >= 'a' && s[a+1] <= 'z')
						&& (a > 0 && !(s[a-1] >= 'a' && s[a-1] <= 'z')))
						putchar(s[a]-'a'+'A');
					else putchar(s[a]);
				}else	putchar(s[a]-'a'+'A'), flag = 1;
			} else {
				if(s[a] == '!' || s[a] == '.' || s[a] == '?')	flag = 0;
				putchar(s[a]);
			}
		}
		puts("");
	}
	return 0;
}
