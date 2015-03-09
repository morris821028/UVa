#include<stdio.h>
#include<string.h>
int main() {
	int k = 0;
	char s[15];
	while(scanf("%s", s) == 1) {
		if(s[0] == '#')	break;
		printf("Case %d: ", ++k);
		if(!strcmp(s, "HELLO"))
			puts("ENGLISH");
		else if(!strcmp(s, "HOLA"))
			puts("SPANISH");
		else if(!strcmp(s, "HALLO"))
			puts("GERMAN");
		else if(!strcmp(s, "BONJOUR"))
			puts("FRENCH");
		else if(!strcmp(s, "CIAO"))
			puts("ITALIAN");
		else if(!strcmp(s, "ZDRAVSTVUJTE"))
			puts("RUSSIAN");
		else
			puts("UNKNOWN");
	}
	return 0;
}
