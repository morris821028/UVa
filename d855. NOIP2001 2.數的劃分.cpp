#include<stdio.h>
int DP[7][201][201] = {};
main() {
	int a, b, c, d;
	DP[1][1][1] = 1;
	for(a = 1; a <= 5; a++) {
		for(b = 1; b <= 200; b++) {
			DP[1][b][b] = 1;
			for(c = 1; c <= b; c++)
				for(d = c; b+d <= 200; d++) {
					DP[a+1][b+d][d] += DP[a][b][c];
				}
		}
	}
	int n, k, sum;
	while(scanf("%d %d", &n, &k) == 2) {
		sum = 0;
		for(a = 0; a <= 200; a++)
			sum += DP[k][n][a];
		printf("%d\n", sum);
	}
	return 0;
}
