#include <stdio.h>
#include <stdlib.h>
int Ans[1001][3000] = {};
int main() {
	int i, j, last = 0, n;
	Ans[0][0] = 1;
	for(i = 1; i <= 1000; i++) {		
		for(j = 0; j <= last; j++)
			Ans[i][j] = Ans[i-1][j]*i;
		for(j = 0; j <= last; j++) {
			Ans[i][j+1] += Ans[i][j]/10;
			Ans[i][j] %= 10;
		}
		while(Ans[i][j] != 0) {
			Ans[i][j+1] += Ans[i][j]/10;
			Ans[i][j] %= 10;
			j++;
		}	
		last = j;	
	}
	while(scanf("%d", &n) == 1) {
		i = 2999;
		printf("%d!\n", n);
		while(Ans[n][i] == 0)	i--;
		for(; i >= 0; i--)
			printf("%d", Ans[n][i]);
		puts("");
	}
    return 0;
}
