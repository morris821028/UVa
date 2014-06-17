#include<stdio.h>
#define maxL 10000000
char S[maxL], T[maxL];
int main() {
	while(scanf("%s %s", &S, &T) == 2)	{
		int i, j = 0;
		for(i = 0; S[i]; i++) {
			for(; T[j]; j++)
				if(S[i] == T[j])
					{break;}
			if(T[j] == '\0')	break;
			j++;
		}
		if(S[i] == '\0')	puts("Yes");
		else				puts("No");
	}
    return 0;
}
