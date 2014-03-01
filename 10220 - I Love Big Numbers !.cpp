#include<stdio.h>
int P[1001][2600] = {}, Ans[1001] = {};
int Build(int P[][2600]) {
	int i, j, last = 0;
	P[0][0] = 1, Ans[0] = 1;
	P[1][0] = 1, Ans[1] = 1;
	for(i = 2; i <= 1000; i++) {
		for(j = 0; j <= last; j++) {
			P[i][j] += P[i-1][j]*i;
			if(P[i][j] >= 10) {
				P[i][j+1] += P[i][j]/10;
				P[i][j] %= 10;
				if(j+1 > last)	last = j+1;
			}
			Ans[i] += P[i][j];
		}
	}
}
int main() {
	Build(P);
	int n;
	while(scanf("%d", &n) == 1)
		printf("%d\n", Ans[n]);
    return 0;
}
