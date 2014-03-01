#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main() {
    char S[25];
    char C[27]="01230120022455012623010202";
    printf("         NAME                     SOUNDEX CODE\n");
    while(gets(S)) {
        printf("         %-25s%c", S, S[0]);
        int a, L = strlen(S), t = 0, last = C[S[0]-'A'], tmp;
        for(a = 1; a < L && t < 3; a++) {
            if((tmp = C[S[a]-'A']) != last && tmp != '0') {
                printf("%c", tmp), t++;
            }
			last = tmp;
		}
        while(t < 3) printf("0"), t++;
        puts("");
    }
    puts("                   END OF OUTPUT");
    return 0;
}
