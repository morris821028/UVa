#include<stdio.h>
#include<string.h>
int main() {
	int T;
	char s[6];
	scanf("%d", &T);
	while(T--) {
		scanf("%s", s);
		if(strlen(s) == 5)	puts("3");
		else {
			int t = 0;
			if(s[0] == 'o')	t++;
			if(s[1] == 'n')	t++;
			if(s[2] == 'e') t++;
			puts(t >= 2 ? "1" : "2");
		}
	}
    return 0;
}
