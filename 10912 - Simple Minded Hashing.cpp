#include <stdio.h>
#include <string.h> 

int DP[27][27][352];/*[letter][length][sum]*/
void build() {
	int i, j, k;
	memset(DP, 0, sizeof(DP));
	DP[0][0][0] = 1;
	for(i = 1; i <= 26; i++) {
		for(j = 0; j <= i; j++) {
			for(k = 0; k < 352; k++) {
				DP[i][j][k] = DP[i-1][j][k];
				if(j > 0 && k >= i)
				DP[i][j][k] += DP[i-1][j-1][k-i];
			}
		}
	}
}
int main() {
	build();
	int L, S, Case = 0;
	while(scanf("%d %d", &L, &S) == 2) {
		if(L == 0 && S == 0)
			break;
		printf("Case %d: ", ++Case);
		if(L > 26 || S > 351)
			puts("0");
		else
			printf("%d\n", DP[26][L][S]);
	}
    return 0;
}
