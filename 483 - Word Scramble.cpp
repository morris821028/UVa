#include<stdio.h>
int main() {
	char s[1000];
	while(gets(s)) {
		int i, j;
		int st = -1, ed = -1;
		for(i = 0; s[i]; i++) {
			if(s[i] != ' ') {
				st = i, ed = i;
				while(s[ed] != ' ' && s[ed] != '\0')	ed++;
				for(j = ed-1; j >= st; j--)
					printf("%c", s[j]);
				i = ed-1;
			} else
				printf(" ");
		}
		puts("");
	}
    return 0;
}
