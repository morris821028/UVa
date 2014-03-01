#include<stdio.h>
int main() {
	int prime[2002] = {0};
	int i, j, C = 0, t;
	prime[0] = prime[1] = 1;
	for(i = 2; i < 2002; i++)
		if(prime[i] == 0) {
			for(j = 2; i*j < 2002; j++)
				prime[i*j] = 1;
		}
	char s[2002];
	scanf("%d", &t);
	while(t--) {
		scanf("%s", s);
		int asci[128] = {0};
		for(i = 0; s[i]; i++)
			asci[s[i]]++;
		printf("Case %d: ", ++C);
		for(i = 0, j = 0; i < 128; i++)
			if(prime[asci[i]] == 0)
				printf("%c", i), j++;
		if(j == 0)	printf("empty");
		puts("");
	}
    return 0;
}
