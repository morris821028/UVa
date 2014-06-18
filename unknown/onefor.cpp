#include<stdio.h>
#include<string.h>
int main() {
	int i, n;
	while(scanf("%d", &n) == 1) {
		char blank[n], star[2*n+2];
		memset(blank, ' ', sizeof(blank));
		memset(star, '*', sizeof(star));
		blank[n-1] = star[2*n+1] = '\0';
		for(i = 0; i < n; i++) 
			printf("%s%s\n", blank+i, star+2*n-2*i);
	}
    return 0;
}
