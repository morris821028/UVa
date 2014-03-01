#include<stdio.h>
#include<string.h>
main() {
	int T, C = 0, a, b;
	char team[100], judge[100];
	scanf("%d", &T), getchar();
	while(T--) {
		gets(team), gets(judge);
		printf("Case %d: ", ++C);
		if(!strcmp(team, judge))
			puts("Yes");
		else {
			int Lteam, Ljudge;
			for(a = 0, b = 0; team[b]; b++)
				if(team[b] != ' ')	team[a++] = team[b];
			Lteam = a, team[a] = '\0';
			for(a = 0, b = 0; judge[b]; b++)
				if(judge[b] != ' ')	judge[a++] = judge[b];
			Ljudge = a, judge[a] = '\0';
			if(Lteam != Ljudge)	puts("Wrong Answer");
			else {
				a = strcmp(team, judge);
				puts(a ? "Wrong Answer" : "Output Format Error");
			}
		}
	}
	return 0;
}
