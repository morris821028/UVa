#include<stdio.h>
#include<string.h>
int main() {
	char s[50];
	while(scanf("%s", s) == 1) {
		if(!strcmp(s, "0"))
			break;
		int i, j, length = strlen(s);
		int Ans = 0;
		for(i = 1, j = length-1; j >= 0; i++, j--) {
			Ans += (s[j]-'0') * ((1<<i)-1);
		}
		printf("%d\n", Ans);
	}
    return 0;
}
