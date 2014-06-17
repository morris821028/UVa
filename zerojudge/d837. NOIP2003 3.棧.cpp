#include<stdio.h>
main() {
	int DP[19][19] = {}, a, b, c, n;
	int Ans[19]= {}; 
	Ans[1] = 1, DP[1][1] = 1;
	for(a = 1; a < 18; a++) {
		for(b = 1; b <= a; b++) 
			for(c = 1; c <= b+1; c++) 
				DP[a+1][c] += DP[a][b], Ans[a+1] += DP[a][b]; 
	} 
	while(scanf("%d", &n) == 1) {
		printf("%d\n", Ans[n]); 
	}
	return 0; 
}
