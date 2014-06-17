#include<stdio.h>
int main() {
	char s[1000];
	int i;
	while(gets(s)) {
		for(i = 0; s[i]; i++)
			printf("%c", s[i]-7);
		puts("");
	}
    return 0;
}
