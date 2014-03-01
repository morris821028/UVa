#include<stdio.h>
#include<string.h>
char s[1000001], STOP[7] = "STOP!!";
int main() {
	int i, ASCII[128];
	while(gets(s)) {
		if(!strcmp(s, STOP))	break;
		memset(ASCII, 0, sizeof(ASCII));
		for(i = 0; s[i]; i++)
			ASCII[s[i]]++;
		gets(s);
		for(i = 0; s[i]; i++)
			ASCII[s[i]]--;
		for(i = 33; i <= 126; i++)
			if(ASCII[i])
				break;
		puts(i ==  127 ? "yes" : "no");
	}
	return 0;
}
