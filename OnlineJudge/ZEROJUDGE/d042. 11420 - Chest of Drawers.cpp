#include<stdio.h>
main() {
	int n, s, i, j;
	long long DP[70][70][2] = {};/*[total][safe][U(0) or L(1)]*/
	DP[1][1][1] = 1, DP[1][0][0] = 1;
	for(i = 1; i <= 64; i++) {
		for(j = 0; j <= i; j++) {
			DP[i+1][j+1][1] += DP[i][j][1];/*LL*/
			DP[i+1][j][0] += DP[i][j][0] + DP[i][j][1];/*UU LU*/
			DP[i+1][j][1] += DP[i][j][0];/*UL*/
		}
	}
	while(scanf("%d %d", &n, &s) == 2) {
		if(n < 0 && s < 0)	break;
		printf("%lld\n", DP[n][s][0] + DP[n][s][1]);
	}
	return 0;
}
