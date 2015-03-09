#include<stdio.h>
#include<stdlib.h>
#include<string.h>
main() {
	char S[21];
	char C[27]="01230120022455012623010202";
	printf("         NAME                     SOUNDEX CODE\n");
	while(scanf("%s", S) == 1) {
		printf("         %s", S);
		int a, L = strlen(S), t = 0, last = C[S[0]-'A'];
		for(a = 0; a < 25-L; a++) printf(" ");
		printf("%c", S[0]);
		for(a = 1; a < L && t < 3; a++)
			if(C[S[a]-'A'] != '0') {
				if(C[S[a]-'A'] == last)
					{last = 0;continue;}
				printf("%c", C[S[a]-'A']), t++, last = C[S[a]-'A'];
			}
			else last = 0;
		while(t < 3) printf("0"), t++;
		puts("");
	}
	puts("                   END OF OUTPUT");
	return 0;
}
