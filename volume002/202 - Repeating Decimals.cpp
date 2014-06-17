#include<stdio.h>
#include<string.h>
int main() {
	int n, m;
	int mark[3001], i, j;
	while(scanf("%d %d", &n, &m) == 2) {		
		char s[3001], *str = s+1;
		memset(mark, 0, sizeof(mark));
		printf("%d/%d = %d.", n, m, n/m);
		n %= m;
		mark[n] = 1;
		n *= 10;
		for(i = 2; ; i++) {
			*str = n/m + '0', str++;			
			if(mark[n%m])	break;
			mark[n%m] = i;
			n %= m;
			n = n*10;
		}
		int st = mark[n%m], ed = i;
		for(j = 1; j < ed && j <= 50; j++) {
			if(j == st)	printf("(");
			printf("%c", s[j]);
		}
		if(j < ed)	printf("...");
		printf(")\n");	
		printf("   %d = number of digits in repeating cycle\n\n", ed-st);
	}
    return 0;
}
