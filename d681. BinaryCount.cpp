#include<stdio.h>
main() {
	char S[6], D[6], c, d;
	int Ans[6] = {}, a;
	while(scanf("%s", S) == 1) {
		printf("%s", S);
		for(a = 0; a < 5; a++)	Ans[a] = S[a]-'0';
		while(scanf("%s %s%c%c", D, S, &c, &d) == 4) {
			if(D[0] == 'r' || D[1] == 'r') {
				for(a = 0; a < 5; a++)
					Ans[a]|=(S[a]-'0');
				printf("||%s", S);
			}
			else {
				for(a = 0; a < 5; a++)
					Ans[a]&=(S[a]-'0');
				printf("&&%s", S);
			}
			if(d == '\n') break;
		}
		printf(" = ");
		for(a = 0;a < 5; a++)
			printf("%d", Ans[a]);
		puts("");
		for(a = 0; a < 5; a++)
			Ans[a] = 0;
	}
	return 0;
}
